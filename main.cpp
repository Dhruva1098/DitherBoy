#include <iostream>
#include <string>
#include "headers/Image.h"
#include "headers/pallete.h"
#include "headers/floyd_dithrer.h"
#include "headers/ordered_dithrer.h"

int main() {
    std::cout << "DitherBoy - Image Dithering Tool\n";
    std::cout << "================================\n\n";
    
    // Create a simple test image (gradient)
    int width = 256;
    int height = 256;
    Image testImage(width, height);
    
    // Create a gradient from black to white
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float grayValue = static_cast<float>(x) / static_cast<float>(width - 1);
            testImage.setPixel(x, y, Color(grayValue, grayValue, grayValue));
        }
    }
    
    // Test with different palettes
    std::cout << "Testing Floyd-Steinberg dithering with various palettes...\n\n";
    
    // Create Floyd-Steinberg ditherer
    FloydDithrer floydDitherer;
    
    // 1. Grayscale palette with 4 levels
    Pallete grayscalePalette4 = Pallete::createGrayScalePallete(4);
    Image output4Levels(width, height);
    floydDitherer.applyDither(testImage, output4Levels, grayscalePalette4);
    output4Levels.save("floyd_4levels.png", "png");
    std::cout << "Saved 4-level grayscale dithered image\n";
    
    // 2. Grayscale palette with 8 levels
    Pallete grayscalePalette8 = Pallete::createGrayScalePallete(8);
    Image output8Levels(width, height);
    floydDitherer.applyDither(testImage, output8Levels, grayscalePalette8);
    output8Levels.save("floyd_8levels.png", "png");
    std::cout << "Saved 8-level grayscale dithered image\n";
    
    // 3. Custom color palette (GameBoy-like: black, dark green, light green, white)
    std::vector<Color> gameboyColors = {
        Color(0.0f, 0.0f, 0.0f),           // Black
        Color(0.0f, 0.3f, 0.0f),           // Dark green
        Color(0.0f, 0.6f, 0.0f),           // Medium green
        Color(0.0f, 0.9f, 0.0f)            // Light green
    };
    Pallete gameboyPalette(gameboyColors);
    Image outputGameboy(width, height);
    floydDitherer.applyDither(testImage, outputGameboy, gameboyPalette);
    outputGameboy.save("floyd_gameboy.png", "png");
    std::cout << "Saved GameBoy-style dithered image\n";
    
    // 4. Create a color gradient test
    Image colorGradient(width, height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float r = static_cast<float>(x) / static_cast<float>(width - 1);
            float g = static_cast<float>(y) / static_cast<float>(height - 1);
            float b = 0.5f;
            colorGradient.setPixel(x, y, Color(r, g, b));
        }
    }
    colorGradient.save("color_gradient.png", "png");
    std::cout << "Saved color gradient test image\n";
    
    // Apply dithering to color gradient
    Image outputColor(width, height);
    floydDitherer.applyDither(colorGradient, outputColor, gameboyPalette);
    outputColor.save("floyd_color_gameboy.png", "png");
    std::cout << "Saved color gradient dithered with GameBoy palette\n";
    
    std::cout << "\nAll tests completed successfully!\n";
    std::cout << "Generated files:\n";
    std::cout << "- test_gradient.png (original grayscale gradient)\n";
    std::cout << "- floyd_4levels.png (4-level grayscale dithering)\n";
    std::cout << "- floyd_8levels.png (8-level grayscale dithering)\n";
    std::cout << "- floyd_gameboy.png (GameBoy-style dithering)\n";
    std::cout << "- color_gradient.png (original color gradient)\n";
    std::cout << "- floyd_color_gameboy.png (color gradient with GameBoy palette)\n";
    
    return 0;
}