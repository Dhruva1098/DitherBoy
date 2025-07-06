//
// Created by Dhruva Sharma on 18/2/25.
//

#ifndef ORDERED_DITHRER_H
#define ORDERED_DITHRER_H

#include "dithrer.h"
#include <vector>


class OrderedDithrer : public Dither {
  public:
    OrderedDithrer(int bayerSize = 2);
    ~OrderedDithrer() override = default;

    void Dither(const Image& inputImage, Image& outputImage, const Pallete& pallete) override;

  private:
    int bayerSize_;
    std::vector<std::vector<float>> bayerMatrix_;
    void GenerateBayerMatrix();

};



#endif //ORDERED_DITHRER_H
