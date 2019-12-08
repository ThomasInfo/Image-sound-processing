//
// Created by Sofia on 01/12/2019.
//

#include "gtest/gtest.h"
#include "../src/FFT.h"

using namespace std;

TEST (FFTTest, GreyScaleFFTIsComputed) {

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


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}