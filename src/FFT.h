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

FourierTransform DiscreteFourierTransform2D(Channel channel);
FourierTransform FastFourierTransform2D(Channel channel, int dir);
int FFT(int dir,int m,double *x,double *y);
int Powerof2(int n,int *m,int *twopm);
std::vector<std::vector<double>> FastFourierModulus(FourierTransform FFT);

#endif //IMAGE_PROCESSING_FFT_H
