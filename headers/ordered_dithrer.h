//
// Created by Dhruva Sharma on 18/2/25.
//

#ifndef ORDERED_DITHRER_H
#define ORDERED_DITHRER_H

#include "dithrer.h"
#include <vector>


class OrderedDithrer {
  public:
    OrderedDithrer(int bayerSize = 2);
    ~OrderedDithrer() override = default;

    void dithrer(const Image& imputImage, Image& OutputImage, cosnt Pallete& pallete) override;

  private:
    int bayerSize_;
    std::vector<std::vector<float>> bayerMatrix_;
    void GenerateBayerMatrices();

};



#endif //ORDERED_DITHRER_H
