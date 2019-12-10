//
// Created by Sofia on 06/12/2019.
//

#include "Writer.h"

#include <cassert>

using namespace cimg_library;
using namespace std;

Writer::Writer() {}

Writer::~Writer () {}

CImg <int> Writer::createRGBImage (RGBImage image) const {
    size_t height = image.size();
    size_t width = image[0].size();
    size_t spectrum = image[0][0].size();

    assert(height > 0);
    assert(width > 0);
    assert (spectrum > 0);

    CImg <int> cImg (height, width, 1, spectrum);

    for (size_t i (0); i < height; ++i) {
        for (size_t j (0); j < width ; ++j) {
            for (size_t k(0); k < spectrum; ++k) {
                cImg(i,j,0,k) = image[i][j][k];
            }
        }
    }

    return cImg;
}

CImg <int> Writer::createGSImage (Channel image) const {
    size_t height = image.size();
    size_t width = image[0].size();

    assert(height > 0);
    assert(width > 0);

    CImg <int> cImg (height, width);

    for (size_t i (0); i < height; ++i) {
        for (size_t j (0); j < width ; ++j) {
                cImg(i,j) = image[i][j];
        }
    }

    return cImg;
}