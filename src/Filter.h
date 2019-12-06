//
// Created by Sofia on 04/12/2019.
//

#ifndef IMAGE_PROCESSING_FILTER_H
#define IMAGE_PROCESSING_FILTER_H

#include "Reader.h"

#include <vector>

//Implementation of Sobel filter

class Filter {

public:
    Filter();
    Filter(std::vector<std::vector<double>>);
    ~Filter();

    Channel preprocess (Channel image) const;
    Channel filter (Channel image) const;

private:
    std::vector<std::vector<double>> f;
};


#endif //IMAGE_PROCESSING_FILTER_H
