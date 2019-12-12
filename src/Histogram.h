
#ifndef IMAGE_SOUND_PROCESSING_HISTOGRAM_H
#define IMAGE_SOUND_PROCESSING_HISTOGRAM_H

#include <vector>
#include "Reader.h"

//! Typedef
/*! A ImageHistogram represents a 3D histogram of pixels intensity values for a color image.
 * It shows the number of pixels in an image at each different intensity value (red, green AND blue).
 * Each axe of the histogram represents a Channel_Histogram of one color: red, green or blue. */
typedef std::vector <std::vector<std::vector<int>>> ImageHistogram;

//! Typedef
/*! A ChannelHistogram represents a 1D histogram of pixel intensity values, either for a greyscale image or only one color (red, green OR blue).
 * It shows the number of pixels in an image at each different intensity value (black, red, green, OR blue). */
typedef std::vector<int> ChannelHistogram;


//! Histogram class
/*!
 * To compute intensity histograms
 */

class Histogram {

public:

    //! A default constructor
    Histogram();

    //! A destructor
    ~Histogram();

    //! Compute an ImageHistogram from an Image
    /*!
     * @param an Image
     * @return its ImageHistogram
     */
    ImageHistogram computeImageHistogram(RGBImage) const;


    //! Compute a ChannelHistogram from a Channel
    /*!
     * @param a Channel
     * @return its ChannelHistogram
     */
    ChannelHistogram computeChannelHistogram(Channel) const;
};


#endif //IMAGE_SOUND_PROCESSING_HISTOGRAM_H
