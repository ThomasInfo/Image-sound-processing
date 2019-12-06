
#include <iostream>
#include "Histogram.h"

using namespace std;

Histogram::Histogram() {}

Histogram::~Histogram () {}

Image_Histogram Histogram::compute_Image_Histogram(RGBImage image) const {
    int nb_lines = image.size();
    int nb_columns = image[0].size();
    Image_Histogram image_histo(256, vector<vector<int>>(256, vector<int>(256)));

    for ( int nx = 0; nx < nb_lines; nx++) {
        for ( int ny = 0; ny < nb_columns; ny++) {
            int r = image[nx][ny][0]; // red intensity
            int g = image[nx][ny][1]; // blue intensity
            int b = image[nx][ny][2]; // green intensity
            image_histo[r][g][b]++;
        }
    }

    return image_histo;
}


Channel_Histogram Histogram::compute_Channel_Histogram(Channel channel) const {
    int nb_lines = channel.size();
    int nb_columns = channel[0].size();
    Channel_Histogram channel_histo(256);

    for ( int nx = 0; nx < nb_lines; nx++) {
        for ( int ny = 0; ny < nb_columns; ny++) {
            int intensity = channel[nx][ny];
            channel_histo[intensity]+=1;
        }
    }

    return channel_histo;
}