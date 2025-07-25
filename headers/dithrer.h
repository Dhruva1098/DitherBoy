//
// Created by Dhruva Sharma on 18/2/25.
//

#ifndef DITHRER_H
#define DITHRER_H

#include "Image.h"
#include "pallete.h"

class Dither {
  public:
    virtual ~Dither() = default;
    virtual void applyDither(const Image& inputImage, Image& outputImage, const Pallete& pallete) = 0;

  protected:
    Dither() {}
};



#endif //DITHRER_H
