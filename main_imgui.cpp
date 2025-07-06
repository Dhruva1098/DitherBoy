#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "stb_image.h"
#include <string>
#include "headers/Image.h"
#include "headers/floyd_dithrer.h"
#include "headers/atkinson_dithrer.h"
#include "headers/ordered_dithrer.h"
#include "headers/threshold_dithrer.h"
#include "headers/ascii_dithrer.h"
#include "headers/pallete.h"
#include <memory>

// GL loader: glad, glew, gl3w, etc. Not needed for macOS OpenGL 3.2+ core profile
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>
#else
#include <OpenGL/gl3.h>
#endif

GLuint LoadTextureFromFile(const char* filename, int* out_width, int* out_height)
{
    int image_width = 0;
    int image_height = 0;
    int channels = 0;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, &channels, 4);
    if (!image_data)
        return 0;
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);
    *out_width = image_width;
    *out_height = image_height;
    return image_texture;
}

// Helper to convert Image to RGBA8 for OpenGL
static std::vector<unsigned char> ImageToRGBA(const Image& img) {
    int w = img.getWidth(), h = img.getHeight();
    std::vector<unsigned char> data(w * h * 4);
    for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x) {
        Color c = img.getPixel(x, y).Clamped();
        int idx = (y * w + x) * 4;
        data[idx+0] = (unsigned char)(c.r * 255.0f);
        data[idx+1] = (unsigned char)(c.g * 255.0f);
        data[idx+2] = (unsigned char)(c.b * 255.0f);
        data[idx+3] = (unsigned char)(c.a * 255.0f);
    }
    return data;
}

GLuint UploadImageToTexture(const Image& img) {
    int w = img.getWidth(), h = img.getHeight();
    auto data = ImageToRGBA(img);
    GLuint tex = 0;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
    return tex;
}

int main(int, char**)
{
    // Setup GLFW
    if (!glfwInit())
        return 1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on Mac
    GLFWwindow* window = glfwCreateWindow(1280, 720, "DitherBoy ImGui", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 150");

    // DitherBoy state
    static char image_path[512] = "";
    static GLuint image_texture = 0;
    static int image_width = 0, image_height = 0;
    static std::unique_ptr<Image> loaded_image;
    static GLuint dithered_texture = 0;
    static int dithered_width = 0, dithered_height = 0;
    static std::unique_ptr<Image> dithered_image;
    // Algorithm and palette state
    static int algorithm_idx = 0;
    static int palette_idx = 0;
    static int grayscale_levels = 4;
    static int bayer_size = 2;
    static float threshold = 0.5f;
    static int ascii_set_idx = 1;
    static bool detect_edges = true;
    // UI state
    static char status_message[256] = "Ready";
    static bool is_processing = false;
    static char save_path[512] = "output.png";
    // Algorithm/palette names
    const char* algorithms[] = {"Floyd-Steinberg", "Atkinson", "Ordered (Bayer)", "Threshold", "ASCII"};
    const char* palettes[] = {"Grayscale", "GameBoy", "NES", "CGA"};
    const char* ascii_sets[] = {"Basic", "Extended", "Artistic", "Simple", "Shader", "Retro", "Advanced", "Font8x8"};

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("DitherBoy", nullptr, ImGuiWindowFlags_MenuBar);
        
        // Menu bar
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Load Image...", "Ctrl+O")) {
                    // TODO: Add file dialog
                }
                if (ImGui::MenuItem("Save Result...", "Ctrl+S", false, dithered_image != nullptr)) {
                    // TODO: Add save dialog
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit", "Alt+F4")) {
                    glfwSetWindowShouldClose(window, true);
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Help")) {
                if (ImGui::MenuItem("About")) {
                    // TODO: Show about dialog
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        // Status bar
        ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "%s", status_message);
        ImGui::Separator();

        // Image Loading Section
        ImGui::BeginChild("ImageLoading", ImVec2(0, 120), true);
        ImGui::Text("Image Loading");
        ImGui::SameLine();
        if (ImGui::Button("Browse...")) {
            // TODO: Add file dialog
        }
        ImGui::SameLine();
        if (ImGui::Button("Load Image") && strlen(image_path) > 0) {
            is_processing = true;
            strcpy(status_message, "Loading image...");
            
            if (image_texture) { glDeleteTextures(1, &image_texture); image_texture = 0; }
            if (dithered_texture) { glDeleteTextures(1, &dithered_texture); dithered_texture = 0; }
            dithered_image.reset();
            
            loaded_image = std::make_unique<Image>(1,1);
            if (loaded_image->load(image_path)) {
                image_width = loaded_image->getWidth();
                image_height = loaded_image->getHeight();
                image_texture = UploadImageToTexture(*loaded_image);
                sprintf(status_message, "Loaded: %dx%d", image_width, image_height);
            } else {
                loaded_image.reset();
                image_width = image_height = 0;
                strcpy(status_message, "Failed to load image");
            }
            is_processing = false;
        }
        ImGui::InputText("Image Path", image_path, IM_ARRAYSIZE(image_path));
        if (image_texture) {
            ImGui::Text("✓ Image loaded: %dx%d pixels", image_width, image_height);
        }
        ImGui::EndChild();

        ImGui::Spacing();

        // Settings Section
        ImGui::BeginChild("Settings", ImVec2(300, 0), true);
        ImGui::Text("Dithering Settings");
        ImGui::Separator();
        
        // Algorithm selection
        ImGui::Text("Algorithm:");
        ImGui::Combo("##Algorithm", &algorithm_idx, algorithms, IM_ARRAYSIZE(algorithms));
        
        // Palette selection
        ImGui::Text("Palette:");
        ImGui::Combo("##Palette", &palette_idx, palettes, IM_ARRAYSIZE(palettes));
        
        // Algorithm-specific parameters
        ImGui::Spacing();
        ImGui::Text("Parameters:");
        
        if (palette_idx == 0) {
            ImGui::SliderInt("Grayscale Levels", &grayscale_levels, 2, 16);
        }
        
        if (algorithm_idx == 2) {
            ImGui::SliderInt("Bayer Size", &bayer_size, 1, 4);
            ImGui::Text("Matrix: %dx%d", 1 << bayer_size, 1 << bayer_size);
        }
        
        if (algorithm_idx == 3) {
            ImGui::SliderFloat("Threshold", &threshold, 0.0f, 1.0f, "%.2f");
        }
        
        if (algorithm_idx == 4) {
            ImGui::Combo("ASCII Set", &ascii_set_idx, ascii_sets, IM_ARRAYSIZE(ascii_sets));
            ImGui::Checkbox("Detect Edges", &detect_edges);
        }
        
        ImGui::Spacing();
        
        // Dither button
        if (ImGui::Button("Apply Dithering", ImVec2(-1, 0)) && loaded_image && !is_processing) {
            is_processing = true;
            strcpy(status_message, "Processing...");
            
            // Palette selection
            Pallete pal;
            switch (palette_idx) {
                case 0: pal = Pallete::createGrayScalePallete(grayscale_levels); break;
                case 1: pal = Pallete({Color(0.0f,0.0f,0.0f), Color(0.0f,0.3f,0.0f), Color(0.0f,0.6f,0.0f), Color(0.0f,0.9f,0.0f)}); break;
                case 2: pal = Pallete({Color(0.0f,0.0f,0.0f), Color(0.5f,0.0f,0.0f), Color(0.0f,0.0f,0.5f), Color(0.5f,0.0f,0.5f), Color(0.0f,0.5f,0.0f), Color(0.5f,0.5f,0.0f), Color(0.0f,0.5f,0.5f), Color(0.8f,0.8f,0.8f)}); break;
                case 3: pal = Pallete({Color(0.0f,0.0f,0.0f), Color(0.0f,0.8f,0.0f), Color(0.8f,0.0f,0.0f), Color(0.8f,0.8f,0.0f)}); break;
                default: pal = Pallete::createGrayScalePallete(4); break;
            }
            
            // Ditherer selection
            std::unique_ptr<Dither> ditherer;
            switch (algorithm_idx) {
                case 0: ditherer = std::make_unique<FloydDithrer>(); break;
                case 1: ditherer = std::make_unique<AtkinsonDithrer>(); break;
                case 2: ditherer = std::make_unique<OrderedDithrer>(bayer_size); break;
                case 3: ditherer = std::make_unique<ThresholdDithrer>(threshold); break;
                case 4: ditherer = std::make_unique<AsciiDithrer>((AsciiCharSet)ascii_set_idx, detect_edges); break;
                default: ditherer = std::make_unique<FloydDithrer>(); break;
            }
            
            dithered_image = std::make_unique<Image>(*loaded_image);
            ditherer->applyDither(*loaded_image, *dithered_image, pal);
            
            if (dithered_texture) { glDeleteTextures(1, &dithered_texture); dithered_texture = 0; }
            dithered_width = dithered_image->getWidth();
            dithered_height = dithered_image->getHeight();
            dithered_texture = UploadImageToTexture(*dithered_image);
            
            sprintf(status_message, "Dithering complete: %dx%d", dithered_width, dithered_height);
            is_processing = false;
        }
        
        if (is_processing) {
            ImGui::SameLine();
            ImGui::Text("Processing...");
        }
        
        ImGui::EndChild();
        
        ImGui::SameLine();
        
        // Results Section
        ImGui::BeginChild("Results", ImVec2(0, 0), true);
        ImGui::Text("Results");
        ImGui::Separator();
        
        if (image_texture || dithered_texture) {
            float display_width = ImGui::GetContentRegionAvail().x - 20;
            float display_height = (ImGui::GetContentRegionAvail().y - 60) / 2;
            
            // Original image
            if (image_texture) {
                ImGui::Text("Original Image:");
                float scale = std::min(display_width / image_width, display_height / image_height);
                ImGui::Image((void*)(intptr_t)image_texture, 
                           ImVec2(image_width * scale, image_height * scale));
            }
            
            ImGui::Spacing();
            
            // Dithered image
            if (dithered_texture) {
                ImGui::Text("Dithered Image:");
                float scale = std::min(display_width / dithered_width, display_height / dithered_height);
                ImGui::Image((void*)(intptr_t)dithered_texture, 
                           ImVec2(dithered_width * scale, dithered_height * scale));
                
                ImGui::Spacing();
                ImGui::InputText("Save Path", save_path, IM_ARRAYSIZE(save_path));
                if (ImGui::Button("Save Result")) {
                    if (dithered_image->save(save_path, "png")) {
                        sprintf(status_message, "Saved to: %s", save_path);
                    } else {
                        strcpy(status_message, "Failed to save image");
                    }
                }
            }
        } else {
            ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "No images to display");
            ImGui::Text("Load an image and apply dithering to see results here.");
        }
        
        ImGui::EndChild();
        
        ImGui::End();

        // Show the ImGui demo window
        ImGui::ShowDemoWindow();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
} 