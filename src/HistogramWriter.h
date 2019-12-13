
#ifndef IMAGE_SOUND_PROCESSING_HISTOGRAMWRITER_H
#define IMAGE_SOUND_PROCESSING_HISTOGRAMWRITER_H

#include <string>

#include "Histogram.h"

//! Writes a 3D histogram of an RGBImage in a text file
/*!
 *
 * @param an ImageHistogram imageHisto
 */
void WriteImageHistogram(ImageHistogram imageHisto, std::string filename);

//! Writes the 2D histogram of a Channel in a text file
/*!
 *
 * @param a ChannelHistogram channelHisto
 */
void WriteChannelHistogram(ChannelHistogram channelHisto, std::string filename);


#endif //IMAGE_PROCESSING_HISTOGRAMWRITER_H