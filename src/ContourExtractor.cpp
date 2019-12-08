//
// Created by Sofia on 04/12/2019.
//

#include <iostream>
#include <cmath>

using namespace std;

#include "ContourExtractor.h"
ContourExtractor::ContourExtractor() {}
ContourExtractor::~ContourExtractor() {}

Channel ContourExtractor::preprocess(Channel image) const {
    size_t l = image.size() + 2;
    size_t c = image[0].size() + 2;

    Channel image1 (l, vector<int> (c));


    for (int i = 1; i < l - 1; ++i ) {
        for (int j = 1; j < c - 1; ++j) {
            image1 [i][j] = image [i-1][j-1];
        }
    }
    return image1;
}

Channel ContourExtractor::detectVerticalEdges(Channel image) const {
    vector<vector<double>> filter = {{-1, 0, 1},{-2, 0, 2},{-1, 0, 1}};
    Channel padded = preprocess(image);
    return convolution(padded, filter);
}

Channel ContourExtractor::detectHorizontalEdges(Channel image) const {
    vector<vector<double>> filter = {{-1, -2, -1},{0, 0, 0},{1, 2, 1}};
    Channel padded = preprocess(image);
    return convolution(padded, filter);
}

Channel ContourExtractor::convolution(Channel image, vector<vector<double>> filter) const {
    size_t l = image.size();
    size_t c = image[0].size();
    Channel filtered (l - 2, vector<int> (c - 2));

    for (int i (1); i < l - 1; ++i) {
        for (int j(1); j < c - 1; ++j) {
            double filteredValue = 0.0;
            //filter each pixel
            for (int k(0); k < 3; ++k) {
                for (int l(0); l < 3; ++l) {
                    filteredValue += filter[k][l]*image[i-k+1][j-l+1];
                }
            }
            filtered[i-1][j-1]=filteredValue;
        }
    }

    return filtered;
}

Channel ContourExtractor::detectAllEdges(Channel image) const {
    size_t l = image.size();
    size_t c = image[0].size();

    Channel horizontal = detectHorizontalEdges(image);
    Channel vertical = detectVerticalEdges(image);
    Channel contours (l, vector<int> (c));

    for (size_t i(0); i < l; ++i) {
        for (size_t j(0); j < c; ++j) {
            contours[i][j] = sqrt(pow(vertical[i][j], 2) + pow(horizontal[i][j], 2));
        }
    }

    return contours;
}