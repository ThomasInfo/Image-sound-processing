#include <iostream>
#include "Reader.h"
#include "ContourExtractor.h"
#include "Writer.h"

using namespace cimg_library;
using namespace std;

int main() {

    Reader r;
    ContourExtractor c;
    Writer w;

    string filepath = "../images/";

    int n;
    vector<string> files = {"lenna.jpeg", "mandrill.png", "fruits.png", "girl.png", "lich.png",
                            "monarch.png", "mountain.png", "pool.png", "sails.png", "serrano.png",
                            "tulips.png", "bridge.jpg", "cameraman.jpg", "airplane.jpg" , "sweden.jpg",
                            "house.jpg", "fruits.jpg", "tulips.png"};

    cout << "Choose a test image from the images folder:" << endl;
    for (int i(0); i < files.size(); ++i) {
        cout << "Enter " << i+1 << " for " << files [i] << endl;
    }

    cout << "Enter any other number to process your own image" << endl;

    do {
        cin >> n;
        if ( n >= 1 and n <= files.size()) {
            filepath += files [n-1];
        } else {

            cout << "Enter the path of your file (relative to the src folder):";
            cin >> filepath;
        }
    } while (cin.fail());

    int color;

    do {
        cout << " Enter 0 if your image is in greyscale and 1 if it's in color" << endl;
        cin >> color;
    } while ( (color != 0 and color !=1) or cin.fail());

    int process;

    do {
        cout << " Enter 1 to compute the intensity histograms,"
                " 2 to extract the contours of the image, "
                "3 to compute the Fourier Transform of the image." << endl;

        cin >> process;
    } while ( (process != 1 and process !=2 and process != 3) or cin.fail());

    if (color == 0) {
        if (process == 2) {

            Channel image = r.loadGSImage(filepath);
            Channel filtered = c.detectAllEdges(image);
            CImg<int> cimg = w.createGSImage(filtered);
            cimg.save("../results/contour.jpeg");
            cout << "Your file has been saved as contour.jpeg in the results folder." << endl;
        }
    } else if (color == 1) {
        if (process == 2) {
            Channel image = r.convertColoredToGS(filepath);
            Channel filtered = c.detectAllEdges(image);
            CImg<int> cimg = w.createGSImage(filtered);
            cimg.save("../results/contour.jpeg");
            cout << "Your file has been saved as contour.jpeg in the results folder." << endl;
        }
    }

    return 0;
}