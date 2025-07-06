//
// Created by Dhruva Sharma on 18/2/25.
//

#ifndef COLOR_H
#define COLOR_H

struct Color {
  float r, g, b, a;
  Color();
  Color(float r, float g, float b, float a);
  Color(float r, float g, float b);

  Color Clamped();
  
  // Arithmetic operators
  Color operator-(const Color& other) const;
  Color operator+(const Color& other) const;
  Color operator*(float scalar) const;
};


#endif //COLOR_H
