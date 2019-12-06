//
// Created by Sofia on 04/12/2019.
//

#include "Filter.h"

using namespace std;

Filter::Filter() {}
Filter::Filter(vector<vector<double>> fil) { f = fil;}
Filter::~Filter() {}

Channel Filter::preprocess(Channel image) const {
    size_t l = image.size() + 2;
    size_t c = image[0].size() + 2;


    Channel image1 (l, vector<int> (c));
    for (int i = 1; i < l; ++i ) {
        for (int j = 1; j < c; ++j) {
            image1 [i][j] = image [i-1][j-1];
        }
    }
    return image1;
}

Channel Filter::filter (Channel image) const {
    size_t l = image.size();
    size_t c = image[0].size();

    Channel processed = preprocess(image);
    Channel filtered (l, vector<int> (c));

    for (int i (1); i < l + 2; ++i) {
        for (int j(1); j < c + 2; ++j) {
            double filteredValue = 0.0;
            //filter each pixel
            for (int k(0); k < 3; ++k) {
                for (int l(0); l < 3; ++l) {
                    filteredValue += f[k][l]*processed[i-k+1][j-k+1];
                }
            }
            filtered[i][j]=filteredValue;
        }
    }

}