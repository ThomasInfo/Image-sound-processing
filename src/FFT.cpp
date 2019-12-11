#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "FFT.h"
#include <cassert>

using namespace std;


/*ComplexVector DiscreteFourierTransform2D(Channel channel) {

    int nb_lines = channel.size();
    int nb_columns = channel[0].size();
    ComplexVector FFT2D(nb_lines, vector<Complex>(nb_columns));
    Complex i = sqrt(-1);

    assert (nb_lines > 0);
    assert (nb_columns > 0);

    for ( int k = 0; k < nb_lines; k++) {
        for ( int l = 0; l < nb_columns; l++) {
            Complex F_k_l(0.0, 0.0); // F[k,l] with F the Discrete Fourier Transform
            for ( int nx = 0; nx < nb_lines; nx++) {
                for ( int ny = 0; ny < nb_columns; ny++) {
                    Complex angle = - 2 * i * M_PI * (nx * k / nb_lines + ny * l / nb_columns);
                    F_k_l += channel[nx][ny] * exp(angle);
                }
            }
            FFT2D[k][l] = F_k_l;
        }
    }

    return FFT2D;
}*/


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
    cout << "N = " << N << endl;
    cout << "M = " << M << endl;
    if (N <= 1 and M <= 1) return;

    if (N%2 == 1) {
        cout << "youyou" << endl;
        ComplexVector temp = image;
        cout << "log" << pow(2, ceil(log2(N)));
        N = pow(2, ceil(log2(N)));
        M = pow(2, ceil(log2(N)));
        cout << "changed" << N << " " << M << endl;
        ComplexVector padded (N, vector<Complex> (M, Complex(0,0)));

        image = padded;

        for (int i(0); i < temp.size(); ++i) {
            for (int j(0); j < temp[0].size(); ++j) {
                image[i][j] = temp[i][j];
            }
        }
    }

    //cout << "N = " << image.size() << endl;
    //cout << "M = " << image[0].size() << endl;




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

    //cout << even_even.size() << endl;
    //cout << even_even[0].size() << endl;
    /*for (int i = 0; i < even_even.size(); ++i) {
        for (int j = 0; j < even_even[0].size(); ++j) {
            cout << even_even[i][j] << endl;
        }
    }*/

    //cout << even_odd.size() << endl;
    //cout << even_odd[0].size() << endl;
    /*for (int i = 0; i < even_odd.size(); ++i) {
        for (int j = 0; j < even_odd[0].size(); ++j) {
            cout << even_odd[i][j] << endl;
        }
    }*/

    //cout << odd_even.size() << endl;
    //cout << odd_even[0].size();
    /*for (int i = 0; i < odd_even.size(); ++i) {
        for (int j = 0; j < odd_even[0].size(); ++j) {
            cout << odd_even[i][j] << endl;
        }
    }*/

    //cout << odd_odd.size() << endl;
    //cout << odd_odd[0].size();
    /*for (int i = 0; i < odd_odd.size(); ++i) {
        for (int j = 0; j < odd_odd[0].size(); ++j) {
            cout << odd_odd[i][j] << endl;
        }
    }*/


    //cout << "even-even" << endl;
    FFT(even_even);
    //cout << "even-odd" << endl;
    FFT(even_odd);
    //cout << "odd-even" << endl;
    FFT(odd_even);
    //cout << "odd-odd" << endl;
    FFT(odd_odd);

    //cout << "base case"<< endl;


    double k = 0;
    double l = 0;

    for (size_t n (0); n < N/2; ++n) {

        for (size_t m(0); m < M/2 ; ++m ) {

            Complex t = Complex(polar(1.0, -2 * M_PI * (k / N + l / M)) * Complex(odd_odd[n][m]));
            Complex t1 = Complex(polar(1.0, -2 * M_PI * (l / M)) * Complex(even_odd[n][m]));
            Complex t2 = Complex(polar(1.0, -2 * M_PI * (k / N)) * Complex(odd_even[n][m]));

            /*cout << polar(1.0, -2 * M_PI * (n / N + m / M)) << odd_odd[n][m] << t << endl;
            cout << polar(1.0, -2 * M_PI * (m / M)) << even_odd[n][m] << t1 << endl;
            cout << polar(1.0, -2 * M_PI * (n / N)) << odd_even[n][m] << t2 << endl;*/


            //cout << n << m << endl;

            //if (N <=2 and M <=2) {

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
            /*} else {

                image[n][m] = even_even[n][m] - t + t1 - t2;
                image[n + N / 2][m + M / 2] = even_even[n][m] - t - t1 + t2;
                image[n + N / 2][m] = even_even[n][m] + t + t1 + t2;
                image[n][m + M / 2] = even_even[n][m] + t - t1 - t2;
            }*/

            //cout << "[" << n << "][" << m << "]" << image[n][m] << endl;
            //cout << "[" << n+N/2 << "][" << m+M/2 << "]" << image[n+N/2][m+M/2] << endl;
            //cout << "[" << n+N/2 << "][" << m << "]" << image[n+N/2][m] << endl;
            //cout << "[" << n << "][" << m+M/2 << "]" << image[n][m+M/2] << endl;



        }
        ++k;
    }

}

void IFFT (ComplexVector& fft) {
    // conjugate the complex numbers
    ComplexVector temp = fft;
    for (int i(0); i < fft.size(); ++i) {
        for (int j(0); j < fft[0].size(); ++j) {
            fft[i][j] = conj(temp[i][j]);
        }
    }

    // forward fft
    FFT(fft);

    temp = fft;
    for (int i(0); i < fft.size(); ++i) {
        for (int j(0); j < fft[0].size(); ++j) {
            fft[i][j] = conj(temp[i][j]);
        }
    }

    // scale the numbers
    for (int i(0); i < fft.size(); ++i) {
        for (int j(0); j < fft[0].size(); ++j) {
            fft[i][j] /= (fft.size()*fft[0].size());
        }
    }
}