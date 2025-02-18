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

};


#endif //COLOR_H
