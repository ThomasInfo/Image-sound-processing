//
// Created by Sofia on 29/11/2019.
//


#ifndef IMAGE_SOUND_PROCESSING_READER_H
#define IMAGE_SOUND_PROCESSING_READER_H

#include <vector>
#include <string>

//Include the libraries for png and jpeg images
#include "../libraries/libpng-1.6.37/png.h"
#include "../libraries/libpng-1.6.37/pnglibconf.h"
#include "../libraries/libjpeg/jpeglib.h"


//#define cimg_use_jpeg 1
//#define cimg_use_png 1


#include "../libraries/CImg.h"
using namespace cimg_library;

//! Typedef
/*! An Image represents a 2D image of pixels (int)
 * with 3 channels (RGB)
 * or 1 channel (greyscale) */
typedef std::vector <std::vector<std::vector<int>>> Image;

//! Typedef
/*! A channel represents a 2D image of pixels (int)
 * in a red/green/blue spectrum */
typedef std::vector<std::vector<int>> Channel;

//! Reader class
/*!
 * To load and manipulate PNG/JPEG images
 */

class Reader {

public:

    //! A default constructor
    Reader();

    //! A destructor
    ~Reader();

    //! Loads a CImg image
    /*!
     *
     * @param filename a string, the path of the file
     * @return an image in the CImg<int> format
     */
    CImg <int> loadCImg(std::string filename) const;

    //! Loads an image into a 1 or 3-channelled 2D vector of int
    /*!
     *
     * @param filename a string, the path of the file
     * @return an Image
     */
    Image loadImage(std::string filename) const;

    //! Extracts the red channel of an image
    /*!
     *
     * @param filename a string, the path of the file
     * @return a Channel
     */
    Channel extractRedChannel (std::string filename) const;

    //! Extracts the green channel of an image
    /*!
     *
     * @param filename a string, the path of the file
     * @return a Channel
     */
    Channel extractBlueChannel (std::string filename) const;

    //! Extracts the blue channel of an image
    /*!
     *
     * @param filename a string, the path of the file
     * @return a Channel
     */
    Channel extractGreenChannel (std::string filename) const;

    //! Converts a CImg type into 1 or 3-channelled 2D image
    /*!
     *
     * @param cImg, to be converted
     * @return an Image
     */
    Image convertImage (CImg <int> cImg) const;

    //! Converts a CImg type into a channel
    /*!
     *
     * @param cImg, to be converted
     * @return a Channel
     */
    Channel convertChannel (CImg <int> cImg) const;


};


#endif //IMAGE_SOUND_PROCESSING_READER_H
