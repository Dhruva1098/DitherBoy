//
// Created by Dhruva Sharma on 18/2/25.
//
#include "headers/ordered_dithrer.h"
#include <vector>
#include <cmath>

OrderedDithrer::OrderedDithrer(int bayerSize) : bayerSize_(bayerSize) {
  GenerateBayerMatrix();
}

void OrderedDithrer::GenerateBayerMatrix() {
  bayerMatrix_.clear();
  if (bayerSize_ < 0) return; // invalid size

  int size = 1 << bayerSize_;
  bayerMatrix_.resize(size, std::vector<float>(size));

  if (size == 1) {
    bayerMatrix_[0][0] = 0.0f;
    return;
  }
  // TODO: Implement proper Bayer matrix generation for larger sizes
}

void OrderedDithrer::Dither(const Image& inputImage, Image& outputImage, const Pallete& pallete) {
  // TODO: Implement ordered dithering algorithm
}

