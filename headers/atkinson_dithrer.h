#ifndef ATKINSON_DITHRER_H
#define ATKINSON_DITHRER_H

#include "error_diffusion_dithrer.h"

class AtkinsonDithrer : public ErrorDiffusionDithrer {
public:
    AtkinsonDithrer();
    ~AtkinsonDithrer() override = default;
    void applyDither(const Image& inputImage, Image& outputImage, const Pallete& pallete) override;
protected:
    void DistributeError(Image& image, int x, int y, const Color& error) override;
};

#endif // ATKINSON_DITHRER_H 