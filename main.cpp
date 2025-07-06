#include <iostream>
#include <string>
#include "headers/Image.h"
#include "headers/pallete.h"
#include "headers/ordered_dithrer.h"

int main() {
    std::cout << "DitherBoy - Ordered Dithering Test\n";
    std::cout << "=================================\n\n";
    
    // Create a simple test image (grayscale gradient)
    int width = 256;
    int height = 256;
    Image testImage(width, height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float grayValue = static_cast<float>(x) / static_cast<float>(width - 1);
            testImage.setPixel(x, y, Color(grayValue, grayValue, grayValue));
        }
    }
    testImage.save("test_gradient.png", "png");
    
    // Palettes
    Pallete grayscale4 = Pallete::createGrayScalePallete(4);
    Pallete grayscale8 = Pallete::createGrayScalePallete(8);
    std::vector<Color> gameboyColors = {
        Color(0.0f, 0.0f, 0.0f),
        Color(0.0f, 0.3f, 0.0f),
        Color(0.0f, 0.6f, 0.0f),
        Color(0.0f, 0.9f, 0.0f)
    };
    Pallete gameboyPalette(gameboyColors);

    // Bayer sizes to test
    std::vector<int> bayerSizes = {1, 2, 3}; // 2x2, 4x4, 8x8
    
    for (int bayer : bayerSizes) {
        OrderedDithrer ditherer(bayer);
        // Grayscale 4-level
        Image outGray4(width, height);
        ditherer.applyDither(testImage, outGray4, grayscale4);
        outGray4.save("ordered_gray4_bayer" + std::to_string(1 << bayer) + ".png", "png");
        std::cout << "Saved ordered_gray4_bayer" << (1 << bayer) << ".png\n";
        // Grayscale 8-level
        Image outGray8(width, height);
        ditherer.applyDither(testImage, outGray8, grayscale8);
        outGray8.save("ordered_gray8_bayer" + std::to_string(1 << bayer) + ".png", "png");
        std::cout << "Saved ordered_gray8_bayer" << (1 << bayer) << ".png\n";
        // GameBoy palette
        Image outGB(width, height);
        ditherer.applyDither(testImage, outGB, gameboyPalette);
        outGB.save("ordered_gameboy_bayer" + std::to_string(1 << bayer) + ".png", "png");
        std::cout << "Saved ordered_gameboy_bayer" << (1 << bayer) << ".png\n";
    }
    
    std::cout << "\nAll ordered dithering tests completed!\n";
    return 0;
}