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
    
    // Test simplified ASCII art
    AsciiDithrer ditherer(AsciiCharSet::FONT8X8, true);
    if (ditherer.saveAsTextSimplified(inputImage, "simplified_ascii.txt")) {
        std::cout << "Generated simplified_ascii.txt\n";
    } else {
        std::cout << "Failed to generate simplified_ascii.txt\n";
    }
    
    return 0;
} 