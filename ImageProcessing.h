#pragma once
#include "image.h"
#include <vector>

class ImageProcessing {
public:
    virtual void process(const Image& src, Image& dst) = 0;
};

class Brightness_contrast : public ImageProcessing {
private:
    int alpha, beta;
public:
    Brightness_contrast();
    Brightness_contrast(int alpha, int beta);
    void process(const Image& src, Image& dst) override;
    ~Brightness_contrast();
};

class Gamma_correction : public ImageProcessing {
private:
    double gamma;
public:
    Gamma_correction();
    Gamma_correction(double gamma);
    void process(const Image& src, Image& dst) override;
    ~Gamma_correction();
};

class Convolution : public ImageProcessing {
private:
    std::vector<std::vector<int>> kernel;
    unsigned char (*scaleFunc)(int);
public:
    Convolution();
    Convolution(std::vector<std::vector<int>> kernel, unsigned char (*scaleFunc)(int));
    void process(const Image& src, Image& dst) override;
    ~Convolution();
};