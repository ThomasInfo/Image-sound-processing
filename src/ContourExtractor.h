//
// Created by Sofia on 04/12/2019.
//

#ifndef IMAGE_PROCESSING_CONTOUREXTRACTOR_H
#define IMAGE_PROCESSING_CONTOUREXTRACTOR_H

#include "Reader.h"

#include <vector>

//! ContourExtraction class
/*!
 * Implements the Sobel filter to extract contours of an image
 */

class ContourExtractor {

public:
    //! A default constructor
    ContourExtractor();

    //! A destructor
    ~ContourExtractor();

    //! Adds a padding of 0-values all around the value, prepares the image for convolution
    /*!
     *
     * @param image a Channel, the image to be padded
     * @return a Channel, the padded image
     */
    Channel preprocess (Channel image) const;

    //! Extracts vertical contours of an image
    /*!
     *
     * @param image a Channel, the input image
     * @return a Channel, the output image representing the vertical contours of the input
     */
    Channel detectVerticalEdges (Channel image) const;

    //! Extracts horizontal contours of an image
    /*!
     *
     * @param image a Channel, the input image
     * @return a Channel, the output image representing the horizontal contours of the input
     */
    Channel detectHorizontalEdges (Channel image) const;

    //! Applies convolution between an image and a filter
    /*!
     *
     * @param filter, a 2d vector of double
     * @param image, the image to be convoluted with the filter, a Channel
     * @return a Channel, the image convoluted
     */
    Channel convolution (Channel image, std::vector<std::vector<double>> filter) const;

    //! Extracts contours of an image
    /*!
     *
     * @param image a Channel, the input image
     * @return a Channel, the output image representing the contours of the input
     */
    Channel detectAllEdges (Channel image) const;
};


#endif //IMAGE_PROCESSING_CONTOUREXTRACTOR_H
