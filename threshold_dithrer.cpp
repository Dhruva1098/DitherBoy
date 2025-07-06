#include "headers/threshold_dithrer.h"

ThresholdDithrer::ThresholdDithrer(float threshold) : threshold_(threshold) {}

void ThresholdDithrer::applyDither(const Image& inputImage, Image& outputImage, const Pallete& pallete) {
    int width = inputImage.getWidth();
    int height = inputImage.getHeight();
    outputImage = inputImage;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Color orig = inputImage.getPixel(x, y);
            float lum = (orig.r + orig.g + orig.b) / 3.0f;
            float newLum = lum > threshold_ ? 1.0f : 0.0f;
            Color newColor = pallete.GetClosestColor(Color(newLum, newLum, newLum));
            outputImage.setPixel(x, y, newColor);
        }
    }
} 