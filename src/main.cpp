#include <iostream>

//#include <cstdlib>

#include "../libraries/libpng-1.6.37/png.h"
#include "../libraries/libpng-1.6.37/pnglibconf.h"

#define cimg_use_png 1

#include "../libraries/CImg.h"

using namespace cimg_library;
using namespace std;


int main() {
    std::cout << "Hello, World!" << std::endl;

    CImg<int> image("mandrill.png");

    cout << image.height()<< endl;
    cout << image.width() << endl;
    cout << image.spectrum() << endl;
    cout << image.size() << endl;

    /*int* img1 = image.data();
    for(int i=0; i < image.size(); i++) {
        cout << "*img1 value: {}" << *(img1+i);
    }*/

    return 0;
}