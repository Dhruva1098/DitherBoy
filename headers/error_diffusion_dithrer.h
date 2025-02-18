//
// Created by Dhruva Sharma on 18/2/25.
//

#ifndef ERROR_DIFFUSION_DITHRER_H
#define ERROR_DIFFUSION_DITHRER_H

#include "dithrer.h"

class ErrorDiffusionDithrer : public Dithrer{
  public:
    ~ErrorDiffusionDithrer() override = default;

  protected:
    ErrorDiffusionDithrer() {}
    virtual void DistributeError(Image& image, int x, int y, const Color& error) = 0;
};

#endif //ERROR_DIFFUSION_DITHRER_H
