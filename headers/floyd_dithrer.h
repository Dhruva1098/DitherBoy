//
// Created by Dhruva Sharma on 18/2/25.
//

#ifndef FLOYD_DITHRER_H
#define FLOYD_DITHRER_H


#include "error_diffusion_dithrer.h"

class floyd_dithrer : public error_diffusion_dithrer {
public:
  floyd_dithrer();
  ~floyd_dithrer() override = default;

  void Dither(const Image& input_image, Image& output_image, const Pallete& palette) override;

protected:
  void DistributeError(Image& image, int x, int y, const Color& color) override;
};



#endif //FLOYD_DITHRER_H
