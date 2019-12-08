//
// Created by Sofia on 01/12/2019.
//

#include "gtest/gtest.h"
#include "../src/Reader.h"
#include "../src/FFT.cpp"


TEST (fftTest, GreyScaleFFTIsComputed) {

    Reader r;
    Channel image = r.loadGSImage("../images/lenna.jpeg");

    vector<vector<complex<double>>> GS_FFT = Fast_Fourier_Transform(image);

    //Correct size
    EXPECT_EQ(image.size(),512);
    //Correct width
    EXPECT_EQ(image[0].size(),512);
}


TEST (fftTest, ColorsFFTAreComputed) {

    Reader r;
    Channel red = r.extractRedChannel("../images/mandrill.png");
    Channel green = r.extractGreenChannel("../images/mandrill.png");
    Channel blue = r.extractBlueChannel("../images/mandrill.png");

    vector<vector<complex<double>>> red_FFT = Fast_Fourier_Transform(red);
    vector<vector<complex<double>>> green_FFT = Fast_Fourier_Transform(green);
    vector<vector<complex<double>>> blue_FFT = Fast_Fourier_Transform(blue);

    //Correct height
    EXPECT_EQ(red_FFT.size(),480);
    //Correct width
    EXPECT_EQ(red_FFT[0].size(),480);


    //Correct height
    EXPECT_EQ(green_FFT.size(),480);
    //Correct width
    EXPECT_EQ(green_FFT[0].size(),480);

    //Correct height
    EXPECT_EQ(blue_FFT.size(),480);
    //Correct width
    EXPECT_EQ(blue_FFT[0].size(),480);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}