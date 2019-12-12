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


//#define cimg_use_jpeg 1
//#define cimg_use_png 1

#include "Reader.h"
#include "../libraries/CImg.h"

using namespace cimg_library;

//! Writer class
/*!
 * To write images in order to visualize results
 */

class Writer {

public:

    //! A default constructor
    Writer();

    //! A destructor
    ~Writer();

    //! Writes a colored CImg image from a 3D vector of int
    /*!
     *
     * @param image, an RGBImage
     * @return an image in the CImg<int> format
     */
    CImg <int> createRGBImage (RGBImage image) const;

    //! Writes a greyscale CImg image from a 2D vector of int
    /*!
     *
     * @param image, a Channel
     * @return an image in the CImg<int> format
     */
    CImg <int> createGSImage (Channel image) const;

    //! Writes a greyscale CImg image from a 2D vector of double
    /*!
     *
     * @param image, a vector<vector<double>>
     * @return an image in the CImg<double> format
     */
    CImg <double> createFFTImage (std::vector<std::vector<double>> image) const;

    //! Writes a RGB CImg image from 3 Channels
    /*!
     *
     * @param red, the red Channel
     * @param green, the green Channel
     * @param blue, the blue Channel
     * @return an image in the CImg<int> format
     */
    CImg <int> createRGBImage (Channel red, Channel green, Channel blue) const;
};


#endif //IMAGE_PROCESSING_WRITER_H
