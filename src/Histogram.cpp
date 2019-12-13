
#include "Histogram.h"
#include <cassert>

using namespace std;

Histogram::Histogram() {}

Histogram::~Histogram() {}

ImageHistogram Histogram::computeImageHistogram(RGBImage image) const {
    int nb_lines = image.size();
    int nb_columns = image[0].size();
    ImageHistogram image_histo(256, vector<vector<int>>(256, vector<int>(256)));

    assert (nb_lines > 0);
    assert (nb_columns > 0);

    for ( int nx = 0; nx < nb_lines; nx++) {
        for ( int ny = 0; ny < nb_columns; ny++) {
            int r = image[nx][ny][0]; // red intensity
            int g = image[nx][ny][1]; // green intensity
            int b = image[nx][ny][2]; // blue intensity
            image_histo[r][g][b]++;
        }
    }

    return image_histo;
}


ChannelHistogram Histogram::computeChannelHistogram(Channel channel) const {
    int nb_lines = channel.size();
    int nb_columns = channel[0].size();
    ChannelHistogram channel_histo(256);

    assert (nb_lines > 0);
    assert (nb_columns > 0);

    for ( int nx = 0; nx < nb_lines; nx++) {
        for ( int ny = 0; ny < nb_columns; ny++) {
            int intensity = channel[nx][ny];
            channel_histo[intensity]+=1;
        }
    }

    return channel_histo;
}