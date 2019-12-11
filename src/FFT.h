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


//ComplexVector DiscreteFourierTransform2D(Channel channel);
//ComplexVector FastFourierTransform2D(Channel channel, int dir);
//int FFT(int dir,int m,double *x,double *y);
//int Powerof2(int n,int *m,int *twopm);




#endif //IMAGE_PROCESSING_FFT_H
