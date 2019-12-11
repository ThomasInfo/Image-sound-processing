//
// Created by Sofia on 08/12/2019.
//

#ifndef IMAGE_PROCESSING_FFT_H
#define IMAGE_PROCESSING_FFT_H

#include <vector>
#include <complex>
#include "Reader.h"

typedef std::complex<double> Complex;
typedef std::vector<std::vector<Complex>> ComplexVector;


std::vector<std::vector<double>> FFTModulus(ComplexVector FFT);
ComplexVector convertImageInComplex(Channel image);
Channel convertComplexInInt (ComplexVector);
void FFT (ComplexVector& image);
void IFFT (ComplexVector& fft);


#endif //IMAGE_PROCESSING_FFT_H
