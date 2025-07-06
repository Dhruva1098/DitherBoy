#include "headers/ascii_dithrer.h"
#include "headers/Image.h"
#include <iostream>

int main() {
    // Load test image
    Image inputImage(1, 1);
    if (!inputImage.load("/Users/dhruvasharma/downloads/test.jpeg")) {
        std::cerr << "Failed to load test.jpeg\n";
        return 1;
    }
    
    std::cout << "Loaded image: " << inputImage.getWidth() << "x" << inputImage.getHeight() << "\n";
    
    // Create ASCII ditherer
    AsciiDithrer ditherer(AsciiCharSet::FONT8X8);
    
    // Test with different scales and colors
    Color black(0, 0, 0);
    Color white(255, 255, 255);
    Color green(0, 255, 0);
    Color red(255, 0, 0);
    
    // Test 1: Black on white, scale 1
    if (ditherer.saveAsAsciiImage(inputImage, "ascii_test_1x.png", black, white, 1)) {
        std::cout << "Generated ascii_test_1x.png\n";
    }
    
    // Test 2: Black on white, scale 2 (larger tiles)
    if (ditherer.saveAsAsciiImage(inputImage, "ascii_test_2x.png", black, white, 2)) {
        std::cout << "Generated ascii_test_2x.png\n";
    }
    
    // Test 3: Green on black (terminal style)
    if (ditherer.saveAsAsciiImage(inputImage, "ascii_test_green.png", green, black, 2)) {
        std::cout << "Generated ascii_test_green.png\n";
    }
    
    // Test 4: Red on white
    if (ditherer.saveAsAsciiImage(inputImage, "ascii_test_red.png", red, white, 2)) {
        std::cout << "Generated ascii_test_red.png\n";
    }
    
    std::cout << "All tests completed!\n";
    return 0;
} 