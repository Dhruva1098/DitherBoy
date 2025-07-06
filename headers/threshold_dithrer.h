#ifndef THRESHOLD_DITHRER_H
#define THRESHOLD_DITHRER_H

#include "dithrer.h"

class ThresholdDithrer : public Dither {
public:
    ThresholdDithrer(float threshold = 0.5f);
    ~ThresholdDithrer() override = default;
    void applyDither(const Image& inputImage, Image& outputImage, const Pallete& pallete) override;
private:
    float threshold_;
};

#endif // THRESHOLD_DITHRER_H 