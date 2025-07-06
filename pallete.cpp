//
// Created by Dhruva Sharma on 18/2/25.
//
#include "headers/pallete.h"
#include <limits>
#include <cmath>
#include <algorithm>

Pallete::Pallete() {}
Pallete::Pallete(const std::vector<Color>& colors) : colors_(colors) {}
Pallete::~Pallete() {}

void Pallete::AddColor(const Color& color){
  colors_.push_back(color);
}

const Color& Pallete::getColor(int index) const {
  if (index >= 0 && index < colors_.size()) {
    return colors_[index];
  } else {
    static const Color black = Color(0.0f, 0.0f, 0.0f);
    return black;
  }
}

int Pallete::getSize() const {
  return colors_.size();
}

const Color& Pallete::GetClosestColor(const Color& color) const {
  if (colors_.empty()) {
    static const Color black = Color(0.0f, 0.0f, 0.0f);
    return black;
  }
  float minDistanceSq = std::numeric_limits<float>::max();
  const Color* closestColor = nullptr;

  for (const auto& palleteColor : colors_) {
    float dr = palleteColor.r - color.r;
    float dg = palleteColor.g - color.g;
    float db = palleteColor.b - color.b;
    float distanceSq = dr * dr + dg * dg + db * db;

    if (distanceSq < minDistanceSq) {
      minDistanceSq = distanceSq;
      closestColor = &palleteColor;
    }
  }
  return *closestColor;
}

Pallete Pallete::createGrayScalePallete(int levels) {
  Pallete pallete;
  if (levels <= 0) return pallete;

  for (int i = 0; i < levels; i++) {
    float grayValue = static_cast<float>(i) / static_cast<float>(levels - 1);
    pallete.AddColor(Color(grayValue, grayValue, grayValue));
  } return pallete;
}


