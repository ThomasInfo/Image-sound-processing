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
                "3 to compute the Fourier Transform of the image." << endl;

        cin >> process;
    } while ( (process != 1 and process !=2 and process != 3) or cin.fail());

    return process;
}

void Run::run(int process, bool color, string filepath) {

    Channel image;
    if (!color) {
        image = r.loadGSImage(filepath);
    } else {
        image = r.convertColoredToGS(filepath);
    }

    if (process==2 ) {
        extractContours(image);
    } else if (process == 3) {
        computeFFT(image);
    } else if (process == 1){
        computeHistogram(image);
    }

}
void Run::extractContours(Channel image) {
    Channel contours = c.detectAllEdges(image);
    CImg<int> cimg = w.createGSImage(contours);
    cimg.save("../results/contour.jpeg");
    cout << "Saved as contour.jpeg in the results folder." << endl;
}

void Run::computeFFT (Channel image) {
    ComplexVector fft = convertImageInComplex(image);
    FFT(fft);
    vector<vector<double>> modulus = FFTModulus(fft);
    CImg<double> cImg = w.createFFTImage(modulus);
    cImg.save("../results/FFT.png");
    cout << "Modulus saved as FFT.png in the results folder." << endl;
}

void Run::computeHistogram(Channel image) {

}