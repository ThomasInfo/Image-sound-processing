
#ifndef IMAGE_SOUND_PROCESSING_HISTROGRAMWRITER_H
#define IMAGE_SOUND_PROCESSING_HISTOGRAMWRITER_H

#include <string>

#include "Histogram.h"

//!
/*!
 *
 * @param an ImageHistogram image_histo
 * @return writes the histogram in a text file
 */
int WriteImageHistogram(ImageHistogram image_histo, string const file_name);

//!
/*!
 *
 * @param a ChannelHistogram channel_histo
 * @return writes the histogram in a text file
 */
int WriteChannelHistogram(ChannelHistogram channel_histo, string const file_name);


#endif //IMAGE_PROCESSING_HISTOGRAMWRITER_H