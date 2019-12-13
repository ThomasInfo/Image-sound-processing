//
// Created by Sofia on 11/12/2019.
//

#include "Run.h"
#include <iostream>
using namespace std;

Run::Run() {}

Run::~Run() {}

string Run::chooseImagePath() {
    string filepath = "../images/";

    int n;
    vector<string> files = {"lenna.jpeg", "mandrill.png", "fruits.png", "girl.png", "lich.png",
                            "monarch.png", "mountain.png", "pool.png", "sails.png", "serrano.png",
                            "tulips.png", "bridge.jpg", "cameraman.jpg", "airplane.jpg" , "sweden.jpeg",
                            "house.jpg", "fruits.jpg", "tulips.png"};

    cout << "Choose a test image from the images folder:" << endl;
    for (int i(0); i < files.size(); ++i) {
        cout << "Enter " << i+1 << " for " << files [i] << endl;
    }

    cout << "Enter any other number to process your own image (.jpeg, .jpg, .png supported)" << endl;

    do {
        cin >> n;
        if ( n >= 1 and n <= files.size()) {
            filepath += files [n-1];
        } else {

            cout << "Enter the path of your file (relative to the src folder):";
            cin >> filepath;
        }
    } while (cin.fail());

    return filepath;
}

bool Run::isColored() {

    int color;

    do {
        cout << "Enter 0 if your image is in greyscale and 1 if it's in color" << endl;
        cin >> color;
    } while ( (color != 0 and color !=1) or cin.fail());

    return (color ==1 );
}

int Run::askUser() {
    int process;

    do {
        cout << "Enter 1 to compute the intensity histograms,"
                " 2 to extract the contours of the image, "
                "3 to compute the Fourier Transform of the image and its inverse." << endl;

        cin >> process;
    } while ( (process != 1 and process !=2 and process != 3) or cin.fail());

    return process;
}

void Run::run(int process, bool color, string filepath) {

    Channel image;
    Channel red;
    Channel blue;
    Channel green;
    RGBImage rgbImage;

    if (!color) {
        image = r.loadGSImage(filepath);
    } else {
        image = r.convertColoredToGS(filepath);
        red = r.extractRedChannel(filepath);
        green = r.extractGreenChannel(filepath);
        blue = r.extractBlueChannel(filepath);
        rgbImage = r.loadRGBImage(filepath);
    }

    if (process==2 ) {
        extractContours(image);
    } else if (process == 3) {
        if (!color) {
            computeFFTandIFFTGS(image);
        } else {
            computeFFTandIFFTColor(filepath);
        }

    } else if (process == 1){
        if (!color) {
            computeHistogram(image, "../histograms/histogram.txt");
        } else {
            computeHistogram(red, "../histograms/red_histogram.txt");
            computeHistogram(blue, "../histograms/blue_histogram.txt");
            computeHistogram(green, "../histograms/green_histogram.txt");
        }

    }

}
void Run::extractContours(Channel image) {
    Channel contours = c.detectAllEdges(image);
    CImg<int> cimg = w.createGSImage(contours);
    cimg.save("../results/contour.jpeg");
    cout << "Saved as contour.jpeg in the results folder." << endl;
}

void Run::computeFFTandIFFTGS (Channel image) {
    ComplexVector fft = convertImageInComplex(image);
    FFT(fft);
    vector<vector<double>> modulus = FFTModulus(fft);
    CImg<double> cImgMod = w.createFFTImage(modulus);
    IFFT(fft);
    Channel reconstructed = convertComplexInInt(fft);
    CImg<int> cImg = w.createGSImage(reconstructed);
    cImgMod.save("../results/FFT.png");
    cImg.save("../results/reconstructed.png");
    cout << "Modulus of FFT saved as FFT.png in the results folder." << endl;
    cout << "Inverse FFT saved as reconstructed.png in the results folder" << endl;
}

void Run::computeFFTandIFFTColor(std::string filepath) {
    Channel red = r.extractRedChannel(filepath);
    Channel green = r.extractGreenChannel(filepath);
    Channel blue = r.extractBlueChannel(filepath);
    ComplexVector fftRed = convertImageInComplex(red);
    ComplexVector fftGreen = convertImageInComplex(green);
    ComplexVector fftBlue = convertImageInComplex(blue);
    FFT(fftRed);
    FFT(fftGreen);
    FFT(fftBlue);
    vector<vector<double>> modulusRed = FFTModulus(fftRed);
    vector<vector<double>> modulusGreen = FFTModulus(fftGreen);
    vector<vector<double>> modulusBlue = FFTModulus(fftBlue);
    CImg<double> cImgModR = w.createFFTImage(modulusRed);
    CImg<double> cImgModG = w.createFFTImage(modulusGreen);
    CImg<double> cImgModB = w.createFFTImage(modulusBlue);
    cImgModR.save("../results/FFT_red.png");
    cImgModG.save("../results/FFT_green.png");
    cImgModB.save("../results/FFT_blue.png");
    IFFT(fftRed);
    IFFT(fftGreen);
    IFFT(fftBlue);
    Channel reconstructedR = convertComplexInInt(fftRed);
    Channel reconstructedG = convertComplexInInt(fftGreen);
    Channel reconstructedB = convertComplexInInt(fftBlue);
    CImg<int> cImg = w.createRGBImage(reconstructedR,reconstructedG, reconstructedB);
    cImg.save("../results/reconstructed_colored.png");
    cout << "Reconstruction saved as reconstructed_colored.png in the results folder." << endl;
}

void Run::computeHistogram(Channel image, string filepath) {
    ChannelHistogram channel_histo = h.computeChannelHistogram(image);
    WriteChannelHistogram(channel_histo, filepath);
    cout << "Histogram saved as" << filepath << endl;
}