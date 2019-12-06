//#include "CImg.h"
//using namespace cimg_library;
#include<iostream>
#include <array>
#include <vector>

std::vector <int> make_histogram(int image[][2]){
    std::vector <int> histogram(256);
    int nb_rows;
    nb_rows = sizeof(image);
    int nb_columns;
    nb_columns = sizeof(image[0]);
    for( int x = 0; x < nb_columns; x++) {
        for (int y = 0; y < nb_rows; y++) {
            int intensity = image[x][y];
            histogram[intensity]++;
        }
    }
    return histogram;
}

int main() {
    std::cout << "Checking histogram." << std::endl;
    int image[2][2];
    image[0][0] = 3;
    image[0][1] = 10;
    image[1][0] = 60;
    image[1][1] = 10;
    std::vector <int> histo = make_histogram(image);

    
    return 0;
}