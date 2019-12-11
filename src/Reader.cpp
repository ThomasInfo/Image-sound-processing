//
// Created by Sofia on 29/11/2019.
//

#include <iostream>
#include "Reader.h"
#include <cassert>

using namespace cimg_library;
using namespace std;

Reader::Reader() {}

Reader::~Reader () {}

CImg <int> Reader::loadCImg(std::string filename) const {
    int n = filename.length();
    char filenameInChar [n + 1];
    strcpy(filenameInChar , filename.c_str());

    CImg<int> image (filenameInChar);
    return image;
}

RGBImage Reader::loadRGBImage(string filename) const {
    CImg<int> image = loadCImg(filename);
    return convertImage(image);
}


Channel Reader::loadGSImage(std::string filename) const {
    CImg<int> image = loadCImg(filename);
    return convertChannel(image);
}

Channel Reader::extractRedChannel (string filename) const {
    CImg<int> image = loadCImg(filename);
    //Red channel is the first one
    return convertChannel(image.get_channel(0));
}

Channel Reader::extractBlueChannel (string filename) const {
    CImg<int> image = loadCImg(filename);
    //Blue channel is the third one
    return convertChannel(image.get_channel(2));
}

Channel Reader::extractGreenChannel (string filename) const {
    CImg<int> image = loadCImg(filename);
    //Green channel is the second one
    return convertChannel(image.get_channel(1));
}

RGBImage Reader::convertImage (CImg <int> cImg) const {
    int lines = cImg.height();
    int columns = cImg.width();
    int channels = cImg.spectrum();

    assert(lines > 0);
    assert(columns > 0);
    assert(channels > 0);

    RGBImage image (lines, vector<vector<int>>(columns, vector<int>(channels)));

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

    assert(lines > 0);
    assert (columns > 0);
    //Channel image (lines, vector<int>(columns));

    Channel image (columns, vector<int>(lines));

    for(size_t i(0); i < columns; i++) {
        for (size_t j(0); j < lines; ++j) {
                image[i][j] = cImg(i,j);
        }
    }

    return image;
}

Channel Reader::convertColoredToGS (std::string filename) const {
    Channel red = extractRedChannel(filename);
    Channel blue = extractBlueChannel(filename);
    Channel green = extractGreenChannel(filename);

    size_t l = red.size();
    size_t c = red[0].size();

    assert(l>0);
    assert(c>0);
    assert(blue.size()>0);
    assert(blue[0].size()>0);
    assert(green.size()>0);
    assert(green[0].size()>0);

    Channel greyscale (l, vector <int> (c));

    for (size_t i (0); i < l; ++i) {
        for (size_t j(0); j < c; ++j) {
            //Greyscale version is the average of the 3 channels
            greyscale [i][j] = (red[i][j]+green[i][j]+blue[i][j])/3;
        }
    }

    return greyscale;
}