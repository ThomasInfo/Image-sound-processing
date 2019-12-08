//
// Created by Sofia on 01/12/2019.
//

#include "gtest/gtest.h"
#include "../src/Histogram.h"


TEST (HistogramTest, ImageHistogramIsComputed) {

    Reader r;
    RGBImage image = r.loadRGBImage("../images/mandrill.png");

    Histogram h;
    Image_Histogram image_histo = h.compute_Image_Histogram(image);

    //Correct red channel size
    EXPECT_EQ(image_histo.size(),256);
    //Correct green channel size
    EXPECT_EQ(image_histo[0].size(),256);
    //Correct blue channel size
    EXPECT_EQ(image_histo[0][0].size(),256);
}


TEST (HistogramTest, GreyscaleChannelHistogramIsComputed) {

    Reader r;
    Channel image = r.loadGSImage("../images/lenna.jpeg");

    Histogram h;
    Channel_Histogram channel_histo = h.compute_Channel_Histogram(image);

    //Correct histogram size
    EXPECT_EQ(channel_histo.size(),256);
}


TEST (HistogramTest, ColorChannelsHistogramAreComputed) {

    Reader r;
    Channel red = r.extractRedChannel("../images/mandrill.png");
    Channel green = r.extractGreenChannel("../images/mandrill.png");
    Channel blue = r.extractBlueChannel("../images/mandrill.png");

    Histogram h;
    Channel_Histogram red_histo = h.compute_Channel_Histogram(red);
    Channel_Histogram green_histo = h.compute_Channel_Histogram(green);
    Channel_Histogram blue_histo = h.compute_Channel_Histogram(blue);

    //Correct histogram size
    EXPECT_EQ(red_histo.size(),256);

    //Correct histogram size
    EXPECT_EQ(green_histo.size(),256);

    //Correct histogram size
    EXPECT_EQ( blue_histo.size(),256);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}