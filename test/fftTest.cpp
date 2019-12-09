//
// Created by Sofia on 01/12/2019.
//
#include <iostream>

#include "gtest/gtest.h"
#include "../src/FFT.h"

using namespace std;

TEST (FFTTest, GreyScaleFFTIsComputed) {
    cout << "Please be patient, this test lasts approximately 2000 seconds (half an hour)." << "\n";

    Reader r;
    Channel image = r.loadGSImage("../images/lenna.jpeg");

    FourierTransform GS_FFT = FastFourierTransform(image);
    vector<vector<double >> GS_FFT_modulus = FastFourierModulus(GS_FFT);

    //Correct height
    EXPECT_EQ(GS_FFT.size(),512);
    //Correct width
    EXPECT_EQ(GS_FFT[0].size(),512);
    //Correct height
    EXPECT_EQ(GS_FFT_modulus.size(),512);
    //Correct width
    EXPECT_EQ(GS_FFT_modulus[0].size(),512);
}


TEST (FFTTest, ColorsFFTAreComputed) {
    cout << "Please be patient, this test lasts approximately 7000 seconds (two hours)." << "\n";

    Reader r;
    Channel red = r.extractRedChannel("../images/mandrill.png");
    Channel green = r.extractGreenChannel("../images/mandrill.png");
    Channel blue = r.extractBlueChannel("../images/mandrill.png");

    FourierTransform red_FFT = FastFourierTransform(red);
    FourierTransform green_FFT = FastFourierTransform(green);
    FourierTransform blue_FFT = FastFourierTransform(blue);

    vector<vector<double>> red_FFT_modulus = FastFourierModulus(red_FFT);
    vector<vector<double>> green_FFT_modulus = FastFourierModulus(green_FFT);
    vector<vector<double>> blue_FFT_modulus = FastFourierModulus(blue_FFT);

    //Correct height
    EXPECT_EQ(red_FFT.size(),480);
    //Correct width
    EXPECT_EQ(red_FFT[0].size(),480);
    //Correct height
    EXPECT_EQ(red_FFT_modulus.size(),480);
    //Correct width
    EXPECT_EQ(red_FFT_modulus[0].size(),480);


    //Correct height
    EXPECT_EQ(green_FFT.size(),480);
    //Correct width
    EXPECT_EQ(green_FFT[0].size(),480);
    //Correct height
    EXPECT_EQ(green_FFT_modulus.size(),480);
    //Correct width
    EXPECT_EQ(green_FFT_modulus[0].size(),480);

    //Correct height
    EXPECT_EQ(blue_FFT.size(),480);
    //Correct width
    EXPECT_EQ(blue_FFT[0].size(),480);
    //Correct height
    EXPECT_EQ(blue_FFT_modulus.size(),480);
    //Correct width
    EXPECT_EQ(blue_FFT_modulus[0].size(),480);
}


TEST (FFTTest, BlackFFTIsRight) {

    Channel black_image(10, vector<int>(10, 0)); // creating a black greyscale image Channel

    FourierTransform black_FFT = FastFourierTransform(black_image);
    vector<vector<double >> black_FFT_modulus = FastFourierModulus(black_FFT);

    // correct computation of the Fast Fourier Transform and its modulus
    Complex zero(0.0, 0.0);
    for ( int k = 0; k < 10; k++) {
        for (int l = 0; l < 10; l++) {
            EXPECT_EQ(black_FFT[k][l], zero);
            EXPECT_EQ(black_FFT_modulus[k][l], 0.0);
        }
    }

}


TEST (FTTTest, FFTIsRight) {

    Channel channel = {{1, 9, 6, 5}, {24, -5, 3, 13}, {8, 0, 1, 7}};


}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}