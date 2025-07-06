#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "headers/Image.h"
#include "headers/pallete.h"
#include "headers/ordered_dithrer.h"
#include "headers/atkinson_dithrer.h"
#include "headers/threshold_dithrer.h"
#include "headers/floyd_dithrer.h"
#include "headers/ascii_dithrer.h"

void printUsage(const char* programName) {
    std::cout << "DitherBoy - Image Dithering Tool\n";
    std::cout << "================================\n\n";
    std::cout << "Usage: " << programName << " [OPTIONS] <input_file> <output_file>\n\n";
    std::cout << "Options:\n";
    std::cout << "  -h, --help              Show this help message\n";
    std::cout << "  -m, --method METHOD     Dithering method (floyd, atkinson, ordered, threshold, ascii)\n";
    std::cout << "  -a, --ascii-set SET     ASCII character set (basic, extended, artistic, simple, shader, retro)\n";
    std::cout << "  -p, --palette PALETTE   Color palette (grayscale:N, gameboy, nes, cga)\n";
    std::cout << "  -b, --bayer SIZE        Bayer matrix size for ordered dithering (1-4)\n";
    std::cout << "  -t, --threshold VALUE   Threshold value for threshold dithering (0.0-1.0)\n";
    std::cout << "  -f, --format FORMAT     Output format (png, jpg, bmp)\n";
    std::cout << "  -q, --quality QUALITY   JPEG quality (1-100, default: 95)\n\n";
    std::cout << "Examples:\n";
    std::cout << "  " << programName << " input.png output.png -m floyd -p grayscale:4\n";
    std::cout << "  " << programName << " input.png output.png -m ordered -b 2 -p gameboy\n";
    std::cout << "  " << programName << " input.png output.png -m atkinson -p nes\n";
    std::cout << "  " << programName << " input.png output.png -m threshold -t 0.5 -p cga\n";
    std::cout << "  " << programName << " input.png output.txt -m ascii -a shader\n";
    std::cout << "  " << programName << " input.png output.txt -m ascii -a retro\n\n";
    std::cout << "Palettes:\n";
    std::cout << "  grayscale:N  - N-level grayscale (2-256)\n";
    std::cout << "  gameboy      - Classic GameBoy 4-color green palette\n";
    std::cout << "  nes          - NES 8-color palette\n";
    std::cout << "  cga          - CGA 4-color palette\n";
}

enum class DitherMethod {
    FLOYD,
    ATKINSON,
    ORDERED,
    THRESHOLD,
    ASCII
};

enum class PaletteType {
    GRAYSCALE,
    GAMEBOY,
    NES,
    CGA
};

struct Config {
    std::string inputFile;
    std::string outputFile;
    DitherMethod method = DitherMethod::FLOYD;
    PaletteType paletteType = PaletteType::GRAYSCALE;
    int grayscaleLevels = 4;
    int bayerSize = 2;
    float threshold = 0.5f;
    std::string format = "png";
    int quality = 95;
    AsciiCharSet asciiCharSet = AsciiCharSet::EXTENDED;
    bool detectEdges = true;
};

Pallete createPalette(const Config& config) {
    switch (config.paletteType) {
        case PaletteType::GRAYSCALE:
            return Pallete::createGrayScalePallete(config.grayscaleLevels);
        
        case PaletteType::GAMEBOY: {
            std::vector<Color> colors = {
                Color(0.0f, 0.0f, 0.0f),           // Black
                Color(0.0f, 0.3f, 0.0f),           // Dark green
                Color(0.0f, 0.6f, 0.0f),           // Medium green
                Color(0.0f, 0.9f, 0.0f)            // Light green
            };
            return Pallete(colors);
        }
        
        case PaletteType::NES: {
            std::vector<Color> colors = {
                Color(0.0f, 0.0f, 0.0f),           // Black
                Color(0.5f, 0.0f, 0.0f),           // Red
                Color(0.0f, 0.0f, 0.5f),           // Blue
                Color(0.5f, 0.0f, 0.5f),           // Magenta
                Color(0.0f, 0.5f, 0.0f),           // Green
                Color(0.5f, 0.5f, 0.0f),           // Yellow
                Color(0.0f, 0.5f, 0.5f),           // Cyan
                Color(0.8f, 0.8f, 0.8f)            // White
            };
            return Pallete(colors);
        }
        
        case PaletteType::CGA: {
            std::vector<Color> colors = {
                Color(0.0f, 0.0f, 0.0f),           // Black
                Color(0.0f, 0.8f, 0.0f),           // Green
                Color(0.8f, 0.0f, 0.0f),           // Red
                Color(0.8f, 0.8f, 0.0f)            // Yellow
            };
            return Pallete(colors);
        }
        
        default:
            return Pallete::createGrayScalePallete(4);
    }
}

std::unique_ptr<Dither> createDitherer(const Config& config) {
    switch (config.method) {
        case DitherMethod::FLOYD:
            return std::make_unique<FloydDithrer>();
        case DitherMethod::ATKINSON:
            return std::make_unique<AtkinsonDithrer>();
        case DitherMethod::ORDERED:
            return std::make_unique<OrderedDithrer>(config.bayerSize);
        case DitherMethod::THRESHOLD:
            return std::make_unique<ThresholdDithrer>(config.threshold);
        case DitherMethod::ASCII:
            return std::make_unique<AsciiDithrer>(config.asciiCharSet, config.detectEdges);
        default:
            return std::make_unique<FloydDithrer>();
    }
}

bool parseArguments(int argc, char* argv[], Config& config) {
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        
        if (arg == "-h" || arg == "--help") {
            printUsage(argv[0]);
            return false;
        }
        else if (arg == "-m" || arg == "--method") {
            if (++i >= argc) {
                std::cerr << "Error: Missing method argument\n";
                return false;
            }
            std::string method = argv[i];
            if (method == "floyd") config.method = DitherMethod::FLOYD;
            else if (method == "atkinson") config.method = DitherMethod::ATKINSON;
            else if (method == "ordered") config.method = DitherMethod::ORDERED;
                    else if (method == "threshold") config.method = DitherMethod::THRESHOLD;
        else if (method == "ascii") config.method = DitherMethod::ASCII;
        else {
            std::cerr << "Error: Unknown method '" << method << "'\n";
            return false;
        }
    }
    else if (arg == "-a" || arg == "--ascii-set") {
        if (++i >= argc) {
            std::cerr << "Error: Missing ASCII set argument\n";
            return false;
        }
        std::string asciiSet = argv[i];
        if (asciiSet == "basic") config.asciiCharSet = AsciiCharSet::BASIC;
        else if (asciiSet == "extended") config.asciiCharSet = AsciiCharSet::EXTENDED;
        else if (asciiSet == "artistic") config.asciiCharSet = AsciiCharSet::ARTISTIC;
        else if (asciiSet == "simple") config.asciiCharSet = AsciiCharSet::SIMPLE;
        else if (asciiSet == "shader") config.asciiCharSet = AsciiCharSet::SHADER;
        else if (asciiSet == "retro") config.asciiCharSet = AsciiCharSet::RETRO;
        else if (asciiSet == "advanced") config.asciiCharSet = AsciiCharSet::ADVANCED;
        else if (asciiSet == "font8x8") config.asciiCharSet = AsciiCharSet::FONT8X8;
        else {
            std::cerr << "Error: Unknown ASCII set '" << asciiSet << "'\n";
            return false;
        }
    }
        else if (arg == "-p" || arg == "--palette") {
            if (++i >= argc) {
                std::cerr << "Error: Missing palette argument\n";
                return false;
            }
            std::string palette = argv[i];
            if (palette.find("grayscale:") == 0) {
                config.paletteType = PaletteType::GRAYSCALE;
                config.grayscaleLevels = std::stoi(palette.substr(10));
                if (config.grayscaleLevels < 2 || config.grayscaleLevels > 256) {
                    std::cerr << "Error: Grayscale levels must be between 2 and 256\n";
                    return false;
                }
            }
            else if (palette == "gameboy") config.paletteType = PaletteType::GAMEBOY;
            else if (palette == "nes") config.paletteType = PaletteType::NES;
            else if (palette == "cga") config.paletteType = PaletteType::CGA;
            else {
                std::cerr << "Error: Unknown palette '" << palette << "'\n";
                return false;
            }
        }
        else if (arg == "-b" || arg == "--bayer") {
            if (++i >= argc) {
                std::cerr << "Error: Missing bayer size argument\n";
                return false;
            }
            config.bayerSize = std::stoi(argv[i]);
            if (config.bayerSize < 1 || config.bayerSize > 4) {
                std::cerr << "Error: Bayer size must be between 1 and 4\n";
                return false;
            }
        }
        else if (arg == "-t" || arg == "--threshold") {
            if (++i >= argc) {
                std::cerr << "Error: Missing threshold argument\n";
                return false;
            }
            config.threshold = std::stof(argv[i]);
            if (config.threshold < 0.0f || config.threshold > 1.0f) {
                std::cerr << "Error: Threshold must be between 0.0 and 1.0\n";
                return false;
            }
        }
        else if (arg == "-f" || arg == "--format") {
            if (++i >= argc) {
                std::cerr << "Error: Missing format argument\n";
                return false;
            }
            config.format = argv[i];
        }
        else if (arg == "-q" || arg == "--quality") {
            if (++i >= argc) {
                std::cerr << "Error: Missing quality argument\n";
                return false;
            }
            config.quality = std::stoi(argv[i]);
            if (config.quality < 1 || config.quality > 100) {
                std::cerr << "Error: Quality must be between 1 and 100\n";
                return false;
            }
        }
        else if (arg[0] == '-') {
            std::cerr << "Error: Unknown option '" << arg << "'\n";
            return false;
        }
        else {
            if (config.inputFile.empty()) {
                config.inputFile = arg;
            }
            else if (config.outputFile.empty()) {
                config.outputFile = arg;
            }
            else {
                std::cerr << "Error: Too many arguments\n";
                return false;
            }
        }
    }
    
    if (config.inputFile.empty() || config.outputFile.empty()) {
        std::cerr << "Error: Input and output files are required\n";
        return false;
    }
    
    return true;
}

int main(int argc, char* argv[]) {
    Config config;
    
    if (!parseArguments(argc, argv, config)) {
        return 1;
    }
    
    // Load input image
    Image inputImage(1, 1); // Temporary size, will be set by load()
    if (!inputImage.load(config.inputFile)) {
        std::cerr << "Error: Failed to load input image '" << config.inputFile << "'\n";
        return 1;
    }
    
    std::cout << "Processing image: " << config.inputFile << "\n";
    std::cout << "Output: " << config.outputFile << "\n";
    std::cout << "Method: ";
    switch (config.method) {
        case DitherMethod::FLOYD: std::cout << "Floyd-Steinberg"; break;
        case DitherMethod::ATKINSON: std::cout << "Atkinson"; break;
        case DitherMethod::ORDERED: std::cout << "Ordered (Bayer " << (1 << config.bayerSize) << "x" << (1 << config.bayerSize) << ")"; break;
        case DitherMethod::THRESHOLD: std::cout << "Threshold (" << config.threshold << ")"; break;
        case DitherMethod::ASCII: std::cout << "ASCII"; break;
    }
    std::cout << "\n";
    
    // Create palette
    Pallete palette = createPalette(config);
    std::cout << "Palette: ";
    switch (config.paletteType) {
        case PaletteType::GRAYSCALE: std::cout << "Grayscale (" << config.grayscaleLevels << " levels)"; break;
        case PaletteType::GAMEBOY: std::cout << "GameBoy"; break;
        case PaletteType::NES: std::cout << "NES"; break;
        case PaletteType::CGA: std::cout << "CGA"; break;
    }
    std::cout << "\n\n";
    
    // Handle ASCII dithering specially
    if (config.method == DitherMethod::ASCII) {
        auto asciiDitherer = std::make_unique<AsciiDithrer>(config.asciiCharSet, config.detectEdges);
        if (!asciiDitherer->saveAsText(inputImage, config.outputFile)) {
            std::cerr << "Error: Failed to save ASCII art to '" << config.outputFile << "'\n";
            return 1;
        }
        std::cout << "ASCII art saved to: " << config.outputFile << "\n";
    } else {
        // Create ditherer and apply dithering
        auto ditherer = createDitherer(config);
        Image outputImage(inputImage.getWidth(), inputImage.getHeight());
        
        ditherer->applyDither(inputImage, outputImage, palette);
        
        // Save output image
        if (!outputImage.save(config.outputFile, config.format)) {
            std::cerr << "Error: Failed to save output image '" << config.outputFile << "'\n";
            return 1;
        }
    }
    
    std::cout << "Dithering completed successfully!\n";
    return 0;
}