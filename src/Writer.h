//
// Created by Sofia on 06/12/2019.
//

#ifndef IMAGE_PROCESSING_WRITER_H
#define IMAGE_PROCESSING_WRITER_H

#include <vector>
#include <string>

//Include the libraries for png and jpeg images
#include "../libraries/libpng-1.6.37/png.h"
#include "../libraries/libpng-1.6.37/pnglibconf.h"
#include "../libraries/libjpeg/jpeglib.h"


#define cimg_use_jpeg 1
#define cimg_use_png 1

#include "Reader.h"
#include "../libraries/CImg.h"

using namespace cimg_library;

class Writer {

public:
    CImg <int> createRGBImage (RGBImage image) const;
};


#endif //IMAGE_PROCESSING_WRITER_H
