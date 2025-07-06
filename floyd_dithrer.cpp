//
// Created by Dhruva Sharma on 18/2/25.
//

#include "headers/floyd_dithrer.h"
#include <cmath>

FloydDithrer::FloydDithrer() : ErrorDiffusionDithrer() {}

void FloydDithrer::applyDither(const Image& inputImage, Image& outputImage, const Pallete& palette) {
    // Copy input image to output image
    outputImage = inputImage;
    
    int width = outputImage.getWidth();
    int height = outputImage.getHeight();
    
    // Process each pixel
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Get current pixel color
            Color oldColor = outputImage.getPixel(x, y);
            
            // Find closest color in palette
            Color newColor = palette.GetClosestColor(oldColor);
            
            // Set the new color
            outputImage.setPixel(x, y, newColor);
            
            // Calculate quantization error
            Color error = oldColor - newColor;
            
            // Distribute error to neighboring pixels
            DistributeError(outputImage, x, y, error);
        }
    }
}

void FloydDithrer::DistributeError(Image& image, int x, int y, const Color& error) {
    int width = image.getWidth();
    int height = image.getHeight();
    
    // Floyd-Steinberg error distribution weights:
    //     X   7/16
    // 3/16 5/16 1/16
    
    // Right pixel (x+1, y)
    if (x + 1 < width) {
        Color rightPixel = image.getPixel(x + 1, y);
        rightPixel.r += error.r * 7.0f / 16.0f;
        rightPixel.g += error.g * 7.0f / 16.0f;
        rightPixel.b += error.b * 7.0f / 16.0f;
        image.setPixel(x + 1, y, rightPixel);
    }
    
    // Bottom-left pixel (x-1, y+1)
    if (x - 1 >= 0 && y + 1 < height) {
        Color bottomLeftPixel = image.getPixel(x - 1, y + 1);
        bottomLeftPixel.r += error.r * 3.0f / 16.0f;
        bottomLeftPixel.g += error.g * 3.0f / 16.0f;
        bottomLeftPixel.b += error.b * 3.0f / 16.0f;
        image.setPixel(x - 1, y + 1, bottomLeftPixel);
    }
    
    // Bottom pixel (x, y+1)
    if (y + 1 < height) {
        Color bottomPixel = image.getPixel(x, y + 1);
        bottomPixel.r += error.r * 5.0f / 16.0f;
        bottomPixel.g += error.g * 5.0f / 16.0f;
        bottomPixel.b += error.b * 5.0f / 16.0f;
        image.setPixel(x, y + 1, bottomPixel);
    }
    
    // Bottom-right pixel (x+1, y+1)
    if (x + 1 < width && y + 1 < height) {
        Color bottomRightPixel = image.getPixel(x + 1, y + 1);
        bottomRightPixel.r += error.r * 1.0f / 16.0f;
        bottomRightPixel.g += error.g * 1.0f / 16.0f;
        bottomRightPixel.b += error.b * 1.0f / 16.0f;
        image.setPixel(x + 1, y + 1, bottomRightPixel);
    }
} 