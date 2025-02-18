//
// Created by Dhruva Sharma on 18/2/25.
//

#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include "color.h"

class Image {
  public:
    Image(int width, int height);
    ~Image();

    bool load(const std::string& filename);
    bool save(const std::string& filename, const std::string& format);

    Color getPixel(int x, int y) const;
    void setPixel(int x, int y, const Color& color);

    int getWidth() const;
    int getHeight() const;

  private:
    int width_;
    int height_;
    std::vector<Color> pixels_;
}



#endif //IMAGE_H
