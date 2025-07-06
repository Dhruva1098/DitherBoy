//
// Created by Dhruva Sharma on 18/2/25.
//
#include "headers/color.h"
#include <algorithm>
#include <algorithm>

Color::Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {} // black opaque

Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

Color::Color(float r, float g, float b) : r(r), g(g), b(b), a(1.0f) {}

Color Color::Clamped() {
    return Color(
        std::max(0.0f, std::min(1.0f, r)),
        std::max(0.0f, std::min(1.0f, g)),
        std::max(0.0f, std::min(1.0f, b)),
        std::max(0.0f, std::min(1.0f, a))
    );
}

Color Color::operator-(const Color& other) const {
    return Color(r - other.r, g - other.g, b - other.b, a - other.a);
}

Color Color::operator+(const Color& other) const {
    return Color(r + other.r, g + other.g, b + other.b, a + other.a);
}

