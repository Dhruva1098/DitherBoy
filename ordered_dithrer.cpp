//
// Created by Dhruva Sharma on 18/2/25.
//
#include "headers/ordered_dithrer.h"
#include <vector>
#include <cmath>
#include <functional>

OrderedDithrer::OrderedDithrer(int bayerSize) : bayerSize_(bayerSize) {
  GenerateBayerMatrix();
}

void OrderedDithrer::GenerateBayerMatrix() {
  bayerMatrix_.clear();
  if (bayerSize_ < 0) return; // invalid size

  int size = 1 << bayerSize_;
  bayerMatrix_.resize(size, std::vector<float>(size, 0.0f));

  // Helper lambda for recursive Bayer matrix generation
  std::function<void(int, int, int, int, int)> fillBayer = [&](int x, int y, int s, int value, int step) {
    if (s == 1) {
      bayerMatrix_[y][x] = static_cast<float>(value);
      return;
    }
    int hs = s / 2;
    fillBayer(x,     y,     hs, value,           step * 4);
    fillBayer(x+hs,  y,     hs, value + step,    step * 4);
    fillBayer(x,     y+hs,  hs, value + step*2,  step * 4);
    fillBayer(x+hs,  y+hs,  hs, value + step*3,  step * 4);
  };
  fillBayer(0, 0, size, 0, 1);

  // Normalize to [0, 1]
  float norm = static_cast<float>(size * size);
  for (int y = 0; y < size; ++y) {
    for (int x = 0; x < size; ++x) {
      bayerMatrix_[y][x] = (bayerMatrix_[y][x] + 0.5f) / norm;
    }
  }
}

void OrderedDithrer::applyDither(const Image& inputImage, Image& outputImage, const Pallete& pallete) {
  int width = inputImage.getWidth();
  int height = inputImage.getHeight();
  outputImage = inputImage;
  int size = 1 << bayerSize_;

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      Color orig = inputImage.getPixel(x, y);
      // Use luminance for thresholding (simple average)
      float lum = (orig.r + orig.g + orig.b) / 3.0f;
      float threshold = bayerMatrix_[y % size][x % size];
      float newLum = lum > threshold ? 1.0f : 0.0f;
      Color newColor = pallete.GetClosestColor(Color(newLum, newLum, newLum));
      outputImage.setPixel(x, y, newColor);
    }
  }
}

