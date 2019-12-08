//
// Created by Sofia on 08/12/2019.
//

#ifndef IMAGE_PROCESSING_FFT_H
#define IMAGE_PROCESSING_FFT_H

#include <vector>
#include <complex>
#include "Reader.h"

typedef std::complex<double> Complex;
typedef std::vector<std::vector<Complex>> FourierTransform;

FourierTransform FastFourierTransform(Channel channel);
std::vector<std::vector<double>> FastFourierModulus(FourierTransform FFT);

#endif //IMAGE_PROCESSING_FFT_H
