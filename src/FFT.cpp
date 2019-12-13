#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "FFT.h"
#include <cassert>

using namespace std;

void DiscreteFourierTransform2D(ComplexVector& FFT2D) {

    ComplexVector image = FFT2D;
    int nb_lines = image.size();
    int nb_columns = image[0].size();

    assert (nb_lines > 0);
    assert (nb_columns > 0);

    double k = 0; //for i
    for ( int i = 0; i < nb_lines; ++i) {
        double l = 0; //for j
        for ( int j = 0; j < nb_columns; ++j) {
            Complex F_i_j(0.0, 0.0); // F[k,l] with F the Discrete Fourier Transform
            double n = 0; //for x
            for ( int x = 0; x < nb_lines; ++x) {
                double m = 0; //for y
                for ( int y = 0; y < nb_columns; ++y) {
                    Complex angle = polar(1.0, -2 * M_PI * ( (n*k) / nb_lines + (l*m / nb_columns)));
                    F_i_j += angle*image[x][y];
                    ++m;
                }

                ++n;
            }
            FFT2D[i][j] = F_i_j;
            ++l;
        }
        ++k;
    }

}

vector<vector<double>> FFTModulus(ComplexVector FFT) {

    int nb_lines = FFT.size();
    int nb_columns = FFT[0].size();
    assert (nb_lines > 0);
    assert (nb_columns > 0);
    vector<vector<double>> modulus(nb_lines, vector<double> (nb_columns));

    for ( int k = 0; k < nb_lines; k++) {
        for ( int l = 0; l < nb_columns; l++) {
            modulus[k][l] = abs(FFT[k][l]);
        }
    }

    return modulus;
}

ComplexVector convertImageInComplex(Channel image) {

    size_t N = image.size();
    size_t M = image[0].size();

    ComplexVector complexImage (N, vector<Complex> (M));

    for (int i (0); i < N; ++i) {
        for (int j(0); j < M; ++j) {
            complexImage[i][j] = image[i][j];
        }
    }
    return complexImage;
}

Channel convertComplexInInt (ComplexVector complexImage) {
    size_t N = complexImage.size();
    size_t M = complexImage[0].size();

    Channel image (N, vector<int> (M));


    for (int i (0); i < N; ++i) {
        for (int j(0); j < M; ++j) {
            image[i][j] = complexImage[i][j].real();
        }
    }
    return image;
}

void FFT (ComplexVector& image) {

    size_t N = image.size();
    size_t M = image[0].size();
    if (N <= 1 and M <= 1) return;

    if (N%2 == 1 or M%2 == 1) {
        //Naive algorithm is computed when the dimensions aren't even
        DiscreteFourierTransform2D(image);
        return;
    }

    assert (N>0);
    assert (M> 0);

    Complex zero (0,0);
    ComplexVector even_even (N/2+N%2, vector<Complex> (M/2+M%2));
    ComplexVector odd_odd (N/2,vector<Complex> (M/2));
    ComplexVector odd_even (N/2+N%2, vector<Complex> (M/2));
    ComplexVector even_odd (N/2, vector<Complex> (M/2+M%2));


    for (int i(0); i < image.size(); ++i) {
        for (int j(0); j < image[0].size(); ++j) {
            if (i%2 == 0 and j%2 ==0) {
                even_even [i/2][j/2] = image[i][j];
            } else if (i%2 != 0 and j%2 !=0) {
                odd_odd[i/2][j/2] = image[i][j];
            } else if (i%2 == 0 and j%2 !=0) {
                even_odd[i/2][j/2] = image[i][j];
            } else if (i%2 != 0 and j%2 ==0) {
                odd_even[i/2][j/2] = image[i][j];
            }
        }
    }


    FFT(even_even);
    FFT(even_odd);
    FFT(odd_even);
    FFT(odd_odd);

    double k = 0;
    double l = 0;

    for (size_t n (0); n < N/2; ++n) {

        for (size_t m(0); m < M/2 ; ++m ) {

            Complex t = Complex(polar(1.0, -2 * M_PI * (k / N + l / M)) * Complex(odd_odd[n][m]));
            Complex t1 = Complex(polar(1.0, -2 * M_PI * (l / M)) * Complex(even_odd[n][m]));
            Complex t2 = Complex(polar(1.0, -2 * M_PI * (k / N)) * Complex(odd_even[n][m]));

            ++l;
                if (n%2 == 1) {
                    image[n][m] = even_even[n][m] - t - t1 + t2;
                    image[n + N / 2][m + M / 2] = even_even[n][m] - t + t1 - t2;
                    image[n + N / 2][m] = even_even[n][m] + t - t1 - t2;
                    image[n][m + M / 2] = even_even[n][m] + t + t1 + t2;
                } else {
                    image[n][m] = even_even[n][m] + t + t1 + t2;
                    image[n + N / 2][m + M / 2] = even_even[n][m] + t - t1 - t2;
                    image[n + N / 2][m] = even_even[n][m] - t + t1 - t2;
                    image[n][m + M / 2] = even_even[n][m] - t - t1 + t2;
                }

        }
        ++k;
    }

}

void IFFT (ComplexVector& fft) {

    // Using the property of FFT for real samples
    conjugate(fft);
    FFT(fft);
    conjugate(fft);

    for (int i(0); i < fft.size(); ++i) {
        for (int j(0); j < fft[0].size(); ++j) {
            fft[i][j] /= (fft.size()*fft[0].size());
        }
    }
}

void conjugate (ComplexVector& fft) {
    ComplexVector temp = fft;
    for (int i(0); i < fft.size(); ++i) {
        for (int j(0); j < fft[0].size(); ++j) {
            fft[i][j] = conj(temp[i][j]);
        }
    }
}