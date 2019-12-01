//
// Created by Sofia on 29/11/2019.
//


#ifndef IMAGE_SOUND_PROCESSING_READER_H
#define IMAGE_SOUND_PROCESSING_READER_H

#include <vector>
#include <string>

#include "../libraries/libpng-1.6.37/png.h"
#include "../libraries/libpng-1.6.37/pnglibconf.h"

#define cimg_use_png 1
#include "../libraries/CImg.h"
using namespace cimg_library;

typedef std::vector<std::vector<int>> Channel;
typedef std::vector <std::vector<std::vector<int>>> RGB_Image;

enum IMAGE_TYPE {JPEG, PNG};

class Reader {

public:

    Reader();
    CImg <int> loadCImg(std::string filename) const;

    RGB_Image loadImage(std::string filename) const;

    Channel extractRedChannel (std::string filename) const;

    Channel extractBlueChannel (std::string filename) const;

    Channel extractGreenChannel (std::string filename) const;

    RGB_Image convertImage (CImg <int> cImg) const;

    Channel convertChannel (CImg <int> cImg) const;


};


#endif //IMAGE_SOUND_PROCESSING_READER_H
