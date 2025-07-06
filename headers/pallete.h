//
// Created by Dhruva Sharma on 18/2/25.
//

#ifndef PALLETE_H
#define PALLETE_H
#include <vector>
#include "color.h"

class Pallete {
  public:
    Pallete();
    Pallete(const std::vector<Color> &colors);
    ~Pallete();

    void AddColor(const Color& color);
    const Color& getColor(int index) const;
    int getSize() const;
    static Pallete createGrayScalePallete(int levels);
    const Color& GetClosestColor(const Color& color) const;
  private:
    std::vector<Color> colors_;
};


#endif //PALLETE_H
