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

    FourierTransform GS_FFT = FastFourierTransform2D(image);
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

    FourierTransform red_FFT = FastFourierTransform2D(red);
    FourierTransform green_FFT = FastFourierTransform2D(green);
    FourierTransform blue_FFT = FastFourierTransform2D(blue);

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

    FourierTransform black_FFT = FastFourierTransform2D(black_image);
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
    FourierTransform solution = {{(72.,0), (23+21j), (14-7.225416114969383e-15j), (23.00000000000001-21.000000000000004j)], [(-4.500000000000001-16.454482671904337j), (-9.473720558371165-28.62435565298214j), (-17.49999999999999-14.722431864335451j), (-28.52627944162884+4.375644347017843j)], [(-4.5000000000000036+16.45448267190432j), (-28.5262794416288-4.37564434701787j), (-17.50000000000001+14.722431864335459j), (-9.473720558371188+28.62435565298214j)]]

}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}