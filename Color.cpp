//
// Created by Dhruva Sharma on 18/2/25.
//
#include "headers/color.h"
#include <algorithm>

Color::Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {} // black opaque

Color::Color(float r, float g, float b) : r(r), g(g), b(b), a(1.0f) {}

Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

Color Color::Clamped() {
    return Color(std::clamp(r,0.0f,1.0f), std::clamp(g,0.0f,1.0f), std::clamp(b,0.0f,1.0f), std::clamp(a,0.0f,1.0f));
}

