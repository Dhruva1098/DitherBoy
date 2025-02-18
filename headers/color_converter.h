//
// Created by Dhruva Sharma on 18/2/25.
//

#ifndef COLOR_CONVERTER_H
#define COLOR_CONVERTER_H

#include "color.h"

namespace color_converter {
    Color sRGBToLinear(const Color& color);
    Color LinearToSRGB(const Color& color);
}
#endif //COLOR_CONVERTER_H
