
#ifndef IMAGE_SOUND_PROCESSING_HISTOGRAM_H
#define IMAGE_SOUND_PROCESSING_HISTOGRAM_H

#include <vector>
#include "Reader.h"

//! Typedef
/*! A Image_Histogram represents a 3D histogram of pixels intensity values for a color image.
 * It shows the number of pixels in an image at each different intensity value (red, green AND blue).
 * Each axe of the histogram represents a Channel_Histogram of one color: red, green or blue. */
typedef std::vector <std::vector<std::vector<int>>> Image_Histogram;

//! Typedef
/*! A Channel_Histogram represents a 1D histogram of pixel intensity values, either for a greyscale image or only one color (red, green OR blue).
 * It shows the number of pixels in an image at each different intensity value (black, red, green, OR blue). */
typedef std::vector<std::vector<int>> Channel_Histogram;


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

    //! Compute an Image_Histogram from an Image
    /*!
     * @param an Image
     * @return its Image_Histogram
     */
    Image_Histogram compute_Image_Histogram(Image) const;


    //! Compute a Channel_Histogram from a Channel
    /*!
     * @param a Channel
     * @return its Channel_Histogram
     */
    Channel_Histogram compute_Channel_Histogram(Channel) const;


    //! Extract one of the three Channel_Histograms from an Image_Histogram
    /*!
     * @param an Image_Histogram and the char corresponding to the Channel of interest: 'r', 'g' or 'b'
     * @return the Channel_Histogram of interest
     */
    Channel_Histogram extract_Channel_Histogram(Image_Histogram, char) const;
};


#endif //IMAGE_SOUND_PROCESSING_HISTOGRAM_H
