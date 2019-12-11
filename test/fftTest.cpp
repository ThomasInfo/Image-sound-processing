//
// Created by Sofia on 01/12/2019.
//
#include <iostream>

#include "gtest/gtest.h"
#include "../src/FFT.h"
#include "../src/Writer.h"
#include <cmath>

using namespace std;

/*TEST (FFTTest, GreyScaleFFTIsComputed) {
    cout << "Please be patient, this test lasts approximately 2000 seconds (half an hour)." << "\n";

    Reader r;
    Channel image = r.loadGSImage("../images/lenna.jpeg");

    FourierTransform GS_FFT = FastFourierTransform2D(image, 1);
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

    FourierTransform red_FFT = FastFourierTransform2D(red, 1);
    FourierTransform green_FFT = FastFourierTransform2D(green, 1);
    FourierTransform blue_FFT = FastFourierTransform2D(blue, 1);

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

    FourierTransform black_FFT = FastFourierTransform2D(black_image, 1);
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



*/

TEST(FFTTest, ConvertInComplexWorks) {
    Channel testImage = {{0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, 14, 15}};
    ComplexVector fft = convertImageInComplex(testImage);
    ComplexVector converted = {{0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, 14, 15}};
    EXPECT_EQ(fft, converted);
}

TEST (FFTTest, FFTWorksOnZeros) {

    Channel testImage = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    ComplexVector fft = convertImageInComplex(testImage);
    FFT(fft);
    Complex zero (0,0);
    ComplexVector solution = {{zero, zero, zero, zero},
                              {zero, zero, zero, zero},
                              {zero, zero, zero, zero},
                              {zero, zero, zero, zero}};

    EXPECT_EQ(fft,solution);

}

TEST (FFTTest, FFTWorksOnOnes) {

    Channel testImage = {{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}};
    ComplexVector fft = convertImageInComplex(testImage);
    FFT(fft);
    Complex zero (0,0);
    ComplexVector solution = {{Complex(16,0), zero, zero, zero},
                              {zero, zero, zero, zero},
                              {zero, zero, zero, zero},
                              {zero, zero, zero, zero}};

    EXPECT_EQ(fft,solution);

}

TEST (FFTTest, FFTWorksOn2x2Vector) {

    Channel testImage = {{0, 1}, {2, 3}};
    ComplexVector fft = convertImageInComplex(testImage);
    FFT(fft);
    ComplexVector solution = {{Complex(6,0), Complex(-2,0)},
                              {Complex(-4,0), Complex(0,0)}};

    EXPECT_EQ(fft,solution);

}

TEST (FFTTest, FFTWorksOn2x2Vector2) {

    Channel testImage = {{10, 20}, {30, 40}};
    ComplexVector fft = convertImageInComplex(testImage);
    FFT(fft);
    ComplexVector solution = {{Complex(100,0), Complex(-20,0)},
                              {Complex(-40,0), Complex(0,0)}};

    EXPECT_EQ(fft,solution);

}


TEST (FFTTest, FFTWorksOn4x4Vector) {


    Channel testImage = {{10, 20, 30, 40}, {10, 20, 30, 40}, {10, 20, 30, 40}, {10, 20, 30, 40}};
    ComplexVector fft = convertImageInComplex(testImage);
    FFT(fft);
    Complex zero (0,0);
    ComplexVector solution = {{Complex(400,0), Complex(-80,80), Complex(-80,0), Complex(-80,-80)},
                              {zero, zero,zero, zero},
                              {zero, zero, zero, zero},
                              {zero, zero, zero, zero}};

    EXPECT_EQ(fft,solution);

}

TEST (FFTTest, FFTWorksOn4x4Vector2) {


    Channel testImage = {{11, 22, 33, 44}, {55, 66, 77, 88}, {99, 10, 30, 40}, {10, 20, 30, 40}};
    ComplexVector fft = convertImageInComplex(testImage);
    FFT(fft);
    Complex zero (0,0);
    ComplexVector solution = {{Complex(675,0), Complex(5,94), Complex(15,0), Complex(5,-94)},
                              {Complex(-69,-186), Complex(-89,-6),Complex(-101,2), Complex(-93,10)},
                              {Complex(-97,0), Complex(89,10), Complex(99,0), Complex(89,-10)},
                              {Complex(-69, 186), Complex(-93,-10), Complex(-101,-2), Complex (-89,6)}};

    for (int i(0); i < fft.size(); ++i) {
        for (int j(0); j < fft[0].size(); ++j) {
            EXPECT_NEAR(fft[i][j].real(),solution[i][j].real(), 1e-3);
            EXPECT_NEAR(fft[i][j].imag(),solution[i][j].imag(), 1e-3);
        }
    }


}

TEST (FFTTest, FFTModululusWorkOn4x4Vector) {

    ComplexVector fft = {{Complex(675,0), Complex(5,94), Complex(15,0), Complex(5,-94)},
                              {Complex(-69,-186), Complex(-89,-6),Complex(-101,2), Complex(-93,10)},
                              {Complex(-97,0), Complex(89,10), Complex(99,0), Complex(89,-10)},
                              {Complex(-69, 186), Complex(-93,-10), Complex(-101,-2), Complex (-89,6)}};

    vector<vector<double>> modulus = FFTModulus(fft);

    vector<vector<double>> solution = {{675, 94.133, 15, 94.133},
                                       {198.386, 89.202, 101.02, 93.536},
                                       {97, 89.560, 99, 89.56},
                                       {198.386, 93.536, 101.02, 89.202}};

    for (int i(0); i < fft.size(); ++i) {
        for (int j(0); j < fft[0].size(); ++j) {
            EXPECT_NEAR(modulus[i][j],solution[i][j], 1e-3);
            EXPECT_NEAR(modulus[i][j],solution[i][j], 1e-3);
        }
    }


}

TEST (FFTTest, FFTWorksOn4x4Vector3) {


    Channel testImage = {{0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, 14, 15}};
    ComplexVector fft = convertImageInComplex(testImage);
    FFT(fft);
    ComplexVector solution = {{Complex(120,0), Complex(-8,8), Complex(-8,0), Complex(-8,-8)},
                              {Complex(-32,32), Complex(0,0),Complex(0,0), Complex(0,0)},
                              {Complex(-32,0), Complex(0,0), Complex(0,0), Complex(0,0)},
                              {Complex(-32, -32), Complex(0,0), Complex(0,0), Complex (0,0)}};


    for (int i(0); i < fft.size(); ++i) {
        for (int j(0); j < fft[0].size(); ++j) {
            EXPECT_NEAR(fft[i][j].real(),solution[i][j].real(), 1e-3);
            EXPECT_NEAR(fft[i][j].imag(),solution[i][j].imag(), 1e-3);
        }
    }

}

TEST (FFTTest, FFTWorksOn8x8Vector) {


    Channel testImage = { {1, 2 ,3, 4, 5, 6, 7, 8},
                          { 9, 10 ,11, 12, 13, 14, 15, 16},
                          { 17, 18 ,19, 20, 21, 22, 23, 24},
                              {25, 26 ,27, 28, 29, 30, 31, 32},
                                  { 33, 34 ,35, 36, 37, 38, 39, 40},
                                      { 41, 42 ,43, 44, 45, 46, 47, 48},
                                          {49, 50 , 51, 52, 53, 54, 55, 56},
                                              { 57, 58 ,59, 60, 61, 62, 63, 64}};
    ComplexVector fft = convertImageInComplex(testImage);
    FFT(fft);
    Complex zero (0,0);
    ComplexVector solution = { {Complex(2080,0), Complex(-32, 77.255) ,Complex(-32,32), Complex(-32, 13.255), Complex(-32,0), Complex(-32, -13.255), Complex(-32,-32), Complex(-32, -77.255)},
                               { Complex(-256, 618.039), zero ,zero, zero, zero, zero, zero, zero},
                               { Complex(-256, 256), zero ,zero, zero, zero, zero, zero, zero},
                               {Complex(-256, 106.039), zero ,zero, zero, zero, zero, zero, zero},
                               { Complex(-256, 0), zero ,zero, zero, zero, zero, zero, zero},
                               { Complex(-256, -106.039), zero ,zero, zero, zero, zero, zero, zero},
                               {Complex(-256, -256), zero , zero, zero, zero, zero, zero, zero},
                               { Complex(-256, -618.039), zero ,zero, zero, zero, zero, zero, zero}};


    for (int i(0); i < fft.size(); ++i) {
        for (int j(0); j < fft[0].size(); ++j) {
            EXPECT_NEAR(fft[i][j].real(),solution[i][j].real(), 1e-3);
            EXPECT_NEAR(fft[i][j].imag(),solution[i][j].imag(), 1e-3);
        }
    }

}

TEST (FFTest, FFTLenna) {
    Reader r;
    Writer w;
    Channel image = r.loadGSImage("../images/lenna.jpeg");
    ComplexVector fft = convertImageInComplex(image);
    FFT(fft);
    vector<vector<double>> modulus = FFTModulus(fft);

    CImg<double> cImg = w.createFFTImage(modulus);
    cImg.save("../results/FFT_lenna.png");
}

TEST (FFTest, IFFTLenna) {
    Reader r;
    Writer w;
    Channel image = r.loadGSImage("../images/lenna.jpeg");
    ComplexVector fft = convertImageInComplex(image);
    FFT(fft);
    IFFT(fft);
    Channel reconstructed = convertComplexInInt(fft);
    CImg<int> cImg = w.createGSImage(reconstructed);
    //CImg<double> cImg = w.createFFTImage(modulus);
    cImg.save("../results/reconstructed_lenna.png");
}


TEST (FFTest, FFTMandrill) {
    Reader r;
    Writer w;
    Channel image = r.convertColoredToGS("../images/mandrill.png");
    ComplexVector fft = convertImageInComplex(image);
    FFT(fft);
    vector<vector<double>> modulus = FFTModulus(fft);
    CImg<double> cImg = w.createFFTImage(modulus);
    cImg.save("../results/FFT_mandrill.png");
}

TEST (FFTest, IFFTMandrill) {
    Reader r;
    Writer w;

    Channel red = r.extractRedChannel("../images/mandrill.png");
    Channel green = r.extractGreenChannel("../images/mandrill.png");
    Channel blue = r.extractBlueChannel("../images/mandrill.png");

    ComplexVector fftRed = convertImageInComplex(red);
    ComplexVector fftGreen = convertImageInComplex(green);
    ComplexVector fftBlue = convertImageInComplex(blue);
    FFT(fftRed);
    FFT(fftGreen);
    FFT(fftBlue);
    IFFT(fftRed);
    IFFT(fftGreen);
    IFFT(fftBlue);
    Channel reconstructedR = convertComplexInInt(fftRed);
    Channel reconstructedG = convertComplexInInt(fftGreen);
    Channel reconstructedB = convertComplexInInt(fftBlue);
    CImg<int> cImg = w.createRGBImage(reconstructedR,reconstructedG, reconstructedB);
    //CImg<double> cImg = w.createFFTImage(modulus);
    cImg.save("../results/reconstructed_mandrill.png");
}

TEST (FFTest, FFTFruits) {
    Reader r;
    Writer w;
    Channel image = r.loadGSImage("../images/fruits.jpg");
    ComplexVector fft = convertImageInComplex(image);
    FFT(fft);
    vector<vector<double>> modulus = FFTModulus(fft);
    CImg<double> cImgMod = w.createFFTImage(modulus);
    IFFT(fft);
    Channel reconstructed = convertComplexInInt(fft);
    CImg<int> cImg = w.createGSImage(reconstructed);
    cImgMod.save("../results/FFT_fruits.png");
    cImg.save("../results/reconstructed_fruits.png");
}

TEST (FFTest, IFFTFruitsColored) {
    Reader r;
    Writer w;

    Channel red = r.extractRedChannel("../images/fruits.png");
    Channel green = r.extractGreenChannel("../images/fruits.png");
    Channel blue = r.extractBlueChannel("../images/fruits.png");

    ComplexVector fftRed = convertImageInComplex(red);
    ComplexVector fftGreen = convertImageInComplex(green);
    ComplexVector fftBlue = convertImageInComplex(blue);
    FFT(fftRed);
    FFT(fftGreen);
    FFT(fftBlue);
    IFFT(fftRed);
    IFFT(fftGreen);
    IFFT(fftBlue);
    Channel reconstructedR = convertComplexInInt(fftRed);
    Channel reconstructedG = convertComplexInInt(fftGreen);
    Channel reconstructedB = convertComplexInInt(fftBlue);
    CImg<int> cImg = w.createRGBImage(reconstructedR,reconstructedG, reconstructedB);
    //CImg<double> cImg = w.createFFTImage(modulus);
    cImg.save("../results/reconstructed_fruits_colored.png");
}

/*TEST (FFTest, FFTMountain) {
    Reader r;
    Writer w;
    Channel image = r.loadGSImage("../images/mountain.png");
    ComplexVector fft = convertImageInComplex(image);
    FFT(fft);
    vector<vector<double>> modulus = FFTModulus(fft);
    CImg<double> cImgMod = w.createFFTImage(modulus);
    IFFT(fft);
    Channel reconstructed = convertComplexInInt(fft);
    CImg<int> cImg = w.createGSImage(reconstructed);
    cImgMod.save("../results/FFT_mountain.png");
    cImg.save("../results/reconstructed_mountain.png");
}*/

/*TEST (FFTTest, FFTWorkson3x3) {

    Channel testImage = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
    ComplexVector fft = convertImageInComplex(testImage);
    FFT(fft);
    ComplexVector solution = {{Complex(36,0), Complex(-8,8), Complex(-8,0)},
                              {Complex(-32,32), Complex(0,0),Complex(0,0)},
                              {Complex(-32,0), Complex(0,0), Complex(0,0)}};

    EXPECT_EQ(fft,solution);

}*/

/*TEST (FTTTest, FFTIsRight) {

    Channel channel = {{1, 9, 6, 5}, {24, -5, 3, 13}, {8, 0, 1, 7}};
    ComplexVector fft = convertImageInComplex(channel);

    ComplexVector solution = {{(72,0), (23,21), (14,0), (23,-21)}, {(-4.5,-16.45), (-9.47,-28.62), (-17.5,-14.72), (-28.53,4.38)}, {(-4.5,16.45), (-28.53,-4.38), (-17.5,14.72), (-9.47,28.62)}};
    FFT(fft);

    for ( int k = 0; k < 10; k++) {
        for (int l = 0; l < 10; l++) {
            EXPECT_LT(norm(fft[k][l]-solution[k][l]), 0.1);
        }
    }
}*/


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}