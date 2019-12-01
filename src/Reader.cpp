//
// Created by Sofia on 29/11/2019.
//

#include "Reader.h"

using namespace cimg_library;
using namespace std;

Reader::Reader() {}

CImg <int> Reader::loadCImg(std::string filename) const {
    int n = filename.length();
    char filenameInChar [n + 1];
    strcpy(filenameInChar , filename.c_str());

    CImg<int> image (filenameInChar);
    return image;
}

RGB_Image Reader::loadImage(string filename) const {
    CImg<int> image = loadCImg(filename);
    return convertImage(image);
}

Channel Reader::extractRedChannel (string filename) const {
    CImg<int> image = loadCImg(filename);
    return convertChannel(image.get_channel(0));
}

Channel Reader::extractBlueChannel (string filename) const {
    CImg<int> image = loadCImg(filename);
    return convertChannel(image.get_channel(1));
}

Channel Reader::extractGreenChannel (string filename) const {
    CImg<int> image = loadCImg(filename);
    return convertChannel(image.get_channel(2));
}

RGB_Image Reader::convertImage (CImg <int> cImg) const {
    int lines = cImg.height();
    int columns = cImg.width();
    int channels = cImg.spectrum();

    RGB_Image image (lines, vector<vector<int>>(columns, vector<int>(channels)));

    for(size_t i(0); i < lines; i++) {
        for (size_t j(0); j < columns; ++j) {
            for (size_t k(0); k < channels; ++k) {
                image[i][j][k] = cImg(i,j,k);
            }
        }
    }

    return image;
}

Channel Reader::convertChannel (CImg <int> cImg) const {
    int lines = cImg.height();
    int columns = cImg.width();

    Channel image (lines, vector<int>(columns));

    for(size_t i(0); i < lines; i++) {
        for (size_t j(0); j < columns; ++j) {
                image[i][j] = cImg(i,j);
        }
    }

    return image;
}