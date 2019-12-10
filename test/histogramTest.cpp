//
// Created by Sofia on 01/12/2019.
//

#include "gtest/gtest.h"
#include "../src/Histogram.h"

using namespace std;


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


TEST (HistogramTest, BlackImageHistogramIsRight) {

    RGBImage image(10, vector<vector<int>>(10, vector<int>(3, 0))); // creating a black RGBImage

    Histogram h;
    Image_Histogram image_histo = h.compute_Image_Histogram(image);

    //Correct count of black pixels
    EXPECT_EQ(image_histo[0][0][0],100); // correct number of black pixels
    EXPECT_EQ(image_histo[1][0][0],0); // checking all the other intensity counts are right
    EXPECT_EQ(image_histo[0][1][0],0);
    EXPECT_EQ(image_histo[0][0][1],0);
    for ( int nred = 1; nred < 256; nred++) {
        for (int ngreen = 1; ngreen < 256; ngreen++) {
            for (int nblue = 1; nblue < 256; nblue++) {
                EXPECT_EQ(image_histo[nred][ngreen][nblue], 0);
            }
        }
    }

}


TEST (HistogramTest, WhiteImageHistogramIsRight) {

    RGBImage image(10, vector<vector<int>>(10, vector<int>(3, 255))); // creating a white RGBImage

    Histogram h;
    Image_Histogram image_histo = h.compute_Image_Histogram(image);

    //Correct count of black pixels
    EXPECT_EQ(image_histo[255][255][255],100); // correct number of white pixels
    EXPECT_EQ(image_histo[255][0][0],0); // checking all the other intensity counts are right
    EXPECT_EQ(image_histo[0][255][0],0);
    EXPECT_EQ(image_histo[0][0][255],0);
    for ( int nred = 0; nred < 255; nred++) {
        for (int ngreen = 0; ngreen < 255; ngreen++) {
            for (int nblue = 0; nblue < 255; nblue++) {
                EXPECT_EQ(image_histo[nred][ngreen][nblue], 0);
            }
        }
    }

}


TEST (HistogramTest, ImageHistogramCountsAreRight) {

    Reader r;
    RGBImage image = r.loadRGBImage("../images/mandrill.png");
    Channel red = r.extractRedChannel("../images/mandrill.png");
    Channel green = r.extractGreenChannel("../images/mandrill.png");
    Channel blue = r.extractBlueChannel("../images/mandrill.png");

    Histogram h;
    Image_Histogram image_histo = h.compute_Image_Histogram(image);
    Channel_Histogram red_histo = h.compute_Channel_Histogram(red);
    Channel_Histogram green_histo = h.compute_Channel_Histogram(green);
    Channel_Histogram blue_histo = h.compute_Channel_Histogram(blue);

    int RGB_pixels_count = 0;
    int red_pixels_count = 0;
    int green_pixels_count = 0;
    int blue_pixels_count = 0;

    //Correct count of pixels
    for ( int nred = 0; nred < 256; nred++) {
        red_pixels_count += red_histo[nred];
        green_pixels_count += green_histo[nred];
        blue_pixels_count += blue_histo[nred];
        for (int ngreen = 0; ngreen < 256; ngreen++) {
            for (int nblue = 0; nblue < 256; nblue++) {
                RGB_pixels_count += image_histo[nred][nblue][ngreen];
            }
        }
    }

    EXPECT_EQ(RGB_pixels_count,480 * 480);
    EXPECT_EQ(red_pixels_count + green_pixels_count + blue_pixels_count,480 * 480);

}


TEST (HistogramTest, ImageHistogramAndChannelHistogramsCorrespond) {

    Reader r;
    RGBImage image = r.loadRGBImage("../images/mandrill.png");
    Channel red = r.extractRedChannel("../images/mandrill.png");
    Channel green = r.extractGreenChannel("../images/mandrill.png");
    Channel blue = r.extractBlueChannel("../images/mandrill.png");

    Histogram h;
    Image_Histogram image_histo = h.compute_Image_Histogram(image);
    Channel_Histogram red_histo = h.compute_Channel_Histogram(red);
    Channel_Histogram green_histo = h.compute_Channel_Histogram(green);
    Channel_Histogram blue_histo = h.compute_Channel_Histogram(blue);

    //Corresponding count of red pixels according to the intensity
    int red_RGB_pixels_count = 0;
    for ( int nred = 0; nred < 256; nred++) {
        red_RGB_pixels_count = 0;
        for (int ngreen = 0; ngreen < 256; ngreen++) {
            for (int nblue = 0; nblue < 256; nblue++) {
                red_RGB_pixels_count += image_histo[nred][nblue][ngreen];
            }
        }
        EXPECT_EQ(red_RGB_pixels_count, red_histo[nred]);
    }

    //Corresponding count of green pixels according to the intensity
    int green_RGB_pixels_count = 0;
    for ( int ngreen = 0; ngreen < 256; ngreen++) {
        green_RGB_pixels_count = 0;
        for (int nred = 0; nred < 256; nred++) {
            for (int nblue = 0; nblue < 256; nblue++) {
                green_RGB_pixels_count += image_histo[nred][nblue][ngreen];
            }
        }
        EXPECT_EQ(green_RGB_pixels_count, green_histo[ngreen]);
    }

    //Corresponding count of blue pixels according to the intensity
    int blue_RGB_pixels_count = 0;
    for ( int nblue = 0; nblue < 256; nblue++) {
        blue_RGB_pixels_count = 0;
        for (int nred = 0; nred < 256; nred++) {
            for (int ngreen = 0; ngreen < 256; ngreen++) {
                blue_RGB_pixels_count += image_histo[nred][nblue][ngreen];
            }
        }
        EXPECT_EQ(blue_RGB_pixels_count, blue_histo[nblue]);
    }


}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}