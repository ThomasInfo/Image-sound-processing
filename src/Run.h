//
// Created by Sofia on 11/12/2019.
//

#ifndef IMAGE_PROCESSING_RUN_H
#define IMAGE_PROCESSING_RUN_H

#include "Reader.h"
#include "Writer.h"
#include "ContourExtractor.h"
#include "Histogram.h"
#include "FFT.h"

//! Run class
/*!
 * To run the main program
 */

class Run {
private:
    Reader r;
    Writer w;
    ContourExtractor c;
    Histogram h;

public:
    //! A default constructor
    Run();

    //! A destructor
    ~Run();

    //! Asks the user to choose an image to process
    /*!
     *
     * @return a string, the filepath of the image
     */
    std::string chooseImagePath();

    //! Asks the user if the image is in RGB or greyscale (will be processed differently)
    /*!
     *
     * @return true if the image is colored, false if not
     */
    bool isColored();

    //! Asks the user if he wants to compute an histogram, compute the Fast Fourier Transform or extract contours
    /*!
     *
     * @return 1 for histograms, 2 for the contour extraction, 3 for the FFT
     */
    int askUser();

    //! Process the image according to the user's choice
    /*!
     *
     * @param filepath a string, the path of the file
     * @param color a boolean to know if the image is colored
     * @param process the user's choice of functionality
     */
    void run(int process, bool color, std::string filepath);

    //! Extract the contours of an image and saves it in a .jpeg file
    /*!
     *
     * @param image, a Channel
     */
    void extractContours(Channel image);

    //! Computes the FFT of an image and saves the modulus in a .png file
    /*!
     *
     * @param image, a Channel
     */
    void computeFFT (Channel image);

    //! Computes the histogram of an image
    /*!
     *
     * @param image, a Channel
     */
    void computeHistogram(Channel image);

};


#endif //IMAGE_PROCESSING_RUN_H
