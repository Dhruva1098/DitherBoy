#include "headers/atkinson_dithrer.h"

AtkinsonDithrer::AtkinsonDithrer() : ErrorDiffusionDithrer() {}

void AtkinsonDithrer::applyDither(const Image& inputImage, Image& outputImage, const Pallete& pallete) {
    outputImage = inputImage;
    int width = outputImage.getWidth();
    int height = outputImage.getHeight();
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Color oldColor = outputImage.getPixel(x, y);
            Color newColor = pallete.GetClosestColor(oldColor);
            outputImage.setPixel(x, y, newColor);
            Color error = (oldColor - newColor) * (1.0f / 8.0f); // Atkinson divides error by 8
            DistributeError(outputImage, x, y, error);
        }
    }
}

void AtkinsonDithrer::DistributeError(Image& image, int x, int y, const Color& error) {
    int width = image.getWidth();
    int height = image.getHeight();
    // Atkinson distributes error to 6 neighbors:
    //      X  1  1
    //   1  1  1
    //      1
    int dx[] = {1, 2, -1, 0, 1, 0};
    int dy[] = {0, 0, 1, 1, 1, 2};
    for (int i = 0; i < 6; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
            Color neighbor = image.getPixel(nx, ny);
            neighbor = neighbor + error;
            image.setPixel(nx, ny, neighbor);
        }
    }
} 