#include "ImageProcessing.h"
#include "image.h"
#include <cmath>
#include <iostream>

Brightness_contrast::Brightness_contrast(): alpha{1}, beta{0} {};

Brightness_contrast::Brightness_contrast(int alpha, int beta) {
    this->alpha = alpha;
    this->beta = beta;
}

void Brightness_contrast::process(const Image &src, Image &dst) {
    Image aux(src);
    dst.zeros(src.width(), src.height());
    for (unsigned int i = 0; i < src.height(); i ++)
        for (unsigned int j = 0; j < src.width(); j ++)
            if (alpha * aux.at(i, j) + beta < 0)
                dst.at(i, j) = 0;
            else if (alpha * aux.at(i, j) + beta > 255)
                dst.at(i, j) = 255;
            else
                dst.at(i, j) = alpha * aux.at(i, j) + beta;

}

Brightness_contrast::~Brightness_contrast() {

}

Gamma_correction::Gamma_correction(): gamma{1} {};

Gamma_correction::Gamma_correction(double gamma) {
    this->gamma = gamma;
}

void Gamma_correction::process(const Image &src, Image &dst) {
    Image aux(src);
    dst.zeros(src.width(), src.height());
    for (unsigned int i = 0; i < src.height(); i ++)
        for (unsigned int j = 0; j < src.width(); j ++)
            dst.at(i, j) = (double)pow(aux.at(i, j), gamma);
}

Gamma_correction::~Gamma_correction() {

}

Convolution::Convolution(): kernel{std::vector<std::vector<int>>()}, scaleFunc{[](int x) -> unsigned char {return x;}} {};

Convolution::Convolution(std::vector<std::vector<int>> kernel, unsigned char(*scaleFunc)(int)): kernel(kernel), scaleFunc(scaleFunc) {};

void Convolution::process(const Image &src, Image &dst) {
    Image second_src(src);
    dst.zeros(src.width() - 3 + 1, src.height() - 3 + 1);
    for (unsigned int i = 0; i < src.height() - 3 + 1; i ++)
        for (unsigned int j = 0; j < src.width() - 3 + 1; j ++) {
            Image aux;
            second_src.getROI(aux, i, j, 3, 3);
            int ans = 0;
            int k = (3 - 1) / 2;
            for (int u = 0; u < 3; u++)
                for (int v = 0; v < 3; v ++)
                    ans += kernel.at(u).at(v) * aux.at(u, v);
            dst.at(j, i) = scaleFunc(ans);
            //std::cout << static_cast<int>(dst.at(j, i))<< ' ';
            //std::cout << static_cast<int>(scaleFunc(ans)) << ' ';
        }
}

Convolution::~Convolution() {

}