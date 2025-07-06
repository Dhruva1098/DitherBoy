#include "httplib.h"
#include "../headers/Image.h"
#include "../headers/floyd_dithrer.h"
#include "../headers/atkinson_dithrer.h"
#include "../headers/ordered_dithrer.h"
#include "../headers/threshold_dithrer.h"
#include "../headers/ascii_dithrer.h"
#include "../headers/pallete.h"
#include <memory>
#include <string>
#include <sstream>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;

// Base64 encoding/decoding helpers
std::string base64_encode(const std::vector<unsigned char>& data) {
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string result;
    int val = 0, valb = -6;
    
    for (unsigned char c : data) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            result.push_back(chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) result.push_back(chars[((val << 8) >> (valb + 8)) & 0x3F]);
    while (result.size() % 4) result.push_back('=');
    return result;
}

std::vector<unsigned char> base64_decode(const std::string& encoded) {
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::vector<unsigned char> result;
    int val = 0, valb = -8;
    
    for (char c : encoded) {
        if (c == '=') break;
        auto it = chars.find(c);
        if (it == std::string::npos) continue;
        val = (val << 6) + it;
        valb += 6;
        if (valb >= 0) {
            result.push_back((val >> valb) & 0xFF);
            valb -= 8;
        }
    }
    return result;
}

// Convert Image to base64 PNG
std::string image_to_base64_png(Image& img) {
    // Create temporary file
    std::string temp_file = "/tmp/ditherboy_temp.png";
    if (img.save(temp_file, "png")) {
        // Read file and convert to base64
        std::ifstream file(temp_file, std::ios::binary);
        if (file) {
            std::vector<unsigned char> data((std::istreambuf_iterator<char>(file)),
                                           std::istreambuf_iterator<char>());
            file.close();
            std::remove(temp_file.c_str());
            return base64_encode(data);
        }
    }
    return "";
}

// Convert base64 to Image
std::unique_ptr<Image> base64_to_image(const std::string& base64_data) {
    auto data = base64_decode(base64_data);
    if (data.empty()) return nullptr;
    
    // Write to temporary file
    std::string temp_file = "/tmp/ditherboy_upload.png";
    std::ofstream file(temp_file, std::ios::binary);
    if (file) {
        file.write(reinterpret_cast<const char*>(data.data()), data.size());
        file.close();
        
        // Load image
        auto img = std::make_unique<Image>(1, 1);
        if (img->load(temp_file)) {
            std::remove(temp_file.c_str());
            return img;
        }
    }
    return nullptr;
}

// Create palette from JSON
Pallete create_palette_from_json(const json& palette_json) {
    std::string type = palette_json["type"];
    
    if (type == "grayscale") {
        int levels = palette_json.value("levels", 4);
        return Pallete::createGrayScalePallete(levels);
    }
    else if (type == "gameboy") {
        return Pallete({Color(0.0f,0.0f,0.0f), Color(0.0f,0.3f,0.0f), 
                       Color(0.0f,0.6f,0.0f), Color(0.0f,0.9f,0.0f)});
    }
    else if (type == "nes") {
        return Pallete({Color(0.0f,0.0f,0.0f), Color(0.5f,0.0f,0.0f), 
                       Color(0.0f,0.0f,0.5f), Color(0.5f,0.0f,0.5f),
                       Color(0.0f,0.5f,0.0f), Color(0.5f,0.5f,0.0f), 
                       Color(0.0f,0.5f,0.5f), Color(0.8f,0.8f,0.8f)});
    }
    else if (type == "cga") {
        return Pallete({Color(0.0f,0.0f,0.0f), Color(0.0f,0.8f,0.0f), 
                       Color(0.8f,0.0f,0.0f), Color(0.8f,0.8f,0.0f)});
    }
    
    return Pallete::createGrayScalePallete(4);
}

// Create ditherer from JSON
std::unique_ptr<Dither> create_ditherer_from_json(const json& dither_json) {
    std::string algorithm = dither_json["algorithm"];
    
    if (algorithm == "floyd") {
        return std::make_unique<FloydDithrer>();
    }
    else if (algorithm == "atkinson") {
        return std::make_unique<AtkinsonDithrer>();
    }
    else if (algorithm == "ordered") {
        int bayer_size = dither_json.value("bayer_size", 2);
        return std::make_unique<OrderedDithrer>(bayer_size);
    }
    else if (algorithm == "threshold") {
        float threshold = dither_json.value("threshold", 0.5f);
        return std::make_unique<ThresholdDithrer>(threshold);
    }
    else if (algorithm == "ascii") {
        int ascii_set = dither_json.value("ascii_set", 1);
        bool detect_edges = dither_json.value("detect_edges", true);
        return std::make_unique<AsciiDithrer>((AsciiCharSet)ascii_set, detect_edges);
    }
    
    return std::make_unique<FloydDithrer>();
}

int main() {
    httplib::Server svr;
    
    // Enable CORS
    svr.set_default_headers({
        {"Access-Control-Allow-Origin", "*"},
        {"Access-Control-Allow-Methods", "GET, POST, OPTIONS"},
        {"Access-Control-Allow-Headers", "Content-Type"}
    });
    
    // Handle preflight requests
    svr.Options(".*", [](const httplib::Request&, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
    });
    
    // Serve static files
    svr.set_mount_point("/", "./web_ui/static");
    
    // API endpoint for dithering
    svr.Post("/api/dither", [](const httplib::Request& req, httplib::Response& res) {
        try {
            // Parse JSON request
            json request = json::parse(req.body);
            
            // Extract image data
            std::string image_base64 = request["image"];
            auto input_image = base64_to_image(image_base64);
            if (!input_image) {
                res.status = 400;
                res.set_content("{\"error\": \"Invalid image data\"}", "application/json");
                return;
            }
            
            // Create palette and ditherer
            Pallete palette = create_palette_from_json(request["palette"]);
            auto ditherer = create_ditherer_from_json(request["dither"]);
            
            // Apply dithering
            Image output_image(input_image->getWidth(), input_image->getHeight());
            ditherer->applyDither(*input_image, output_image, palette);
            
            // Convert result to base64
            std::string result_base64 = image_to_base64_png(output_image);
            if (result_base64.empty()) {
                res.status = 500;
                res.set_content("{\"error\": \"Failed to process image\"}", "application/json");
                return;
            }
            
            // Return result
            json response = {
                {"success", true},
                {"image", result_base64},
                {"width", output_image.getWidth()},
                {"height", output_image.getHeight()}
            };
            
            res.set_content(response.dump(), "application/json");
            
        } catch (const std::exception& e) {
            res.status = 500;
            json error_response = {
                {"error", e.what()}
            };
            res.set_content(error_response.dump(), "application/json");
        }
    });
    
    // Health check endpoint
    svr.Get("/api/health", [](const httplib::Request&, httplib::Response& res) {
        json response = {
            {"status", "ok"},
            {"service", "DitherBoy Web API"},
            {"version", "1.0.0"}
        };
        res.set_content(response.dump(), "application/json");
    });
    
    std::cout << "DitherBoy Web Server starting on http://localhost:8080" << std::endl;
    std::cout << "API endpoints:" << std::endl;
    std::cout << "  GET  /api/health - Health check" << std::endl;
    std::cout << "  POST /api/dither - Apply dithering" << std::endl;
    std::cout << "  GET  / - Web UI" << std::endl;
    
    svr.listen("localhost", 8080);
    
    return 0;
} 