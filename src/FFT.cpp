#define _USE_MATH_DEFINES
#include <cmath>

#include "FFT.h"
#include <cassert>

using namespace std;


FourierTransform FastFourierTransform(Channel channel) {

    int nb_lines = channel.size();
    int nb_columns = channel[0].size();
    FourierTransform FFT(nb_lines, vector<Complex>(nb_columns));
    Complex i = sqrt(-1);

    assert (nb_lines > 0);
    assert (nb_columns > 0);

    for ( int k = 0; k < nb_lines; k++) {
        for ( int l = 0; l < nb_columns; l++) {
            Complex F_k_l(0.0, 0.0); // F[k,l] with F the Fast Fourier Transform
            for ( int nx = 0; nx < nb_lines; nx++) {
                for ( int ny = 0; ny < nb_columns; ny++) {
                    Complex angle = - 2 * i * M_PI * (nx * k / nb_lines + ny * l / nb_columns);
                    F_k_l += channel[nx][ny] * exp(angle);
                }
            }
            FFT[k][l] = F_k_l;
        }
    }

    return FFT;
}


vector<vector<double>> FastFourierModulus(FourierTransform FFT) {

    //vector<vector<Complex>> FFT = FastFourierTransform(channel);
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
