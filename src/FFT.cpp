
#include <math.h>
#include "Reader.h"
using namespace std;

vector< vector<complex<double>> > Fast_Fourier_Transform(Channel channel) const {
    int nb_lines = channel.size();
    int nb_columns = channel[0].size();
    vector< nb_lines, vector<complex<double>>(nb_columns) > FFT;

    for ( int k = 0; k < nb_lines; k++) {
        for ( int l = 0; l < nb_columns; l++) {
            complex<double> F_k_l(0.0, 0.0); // F[k,l] with F the Fast Fourier Transform
            for ( int nx = 0; nx < nb_lines; nx++) {
                for ( int ny = 0; ny < nb_columns; ny++) {
                    double angle = - 2 * M_PI * (nx * k / nb_lines + ny * l / nb_columns);
                    F_k_l += channel[nx][ny] * exp(angle);
                }
            }
            FFT[k][l] = F_k_l;
        }
    }

    return FFT;
}
