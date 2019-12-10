#define _USE_MATH_DEFINES
#include <cmath>

#include "FFT.h"

using namespace std;


FourierTransform DiscreteFourierTransform2D(Channel channel) {

    int nb_lines = channel.size();
    int nb_columns = channel[0].size();
    FourierTransform FFT2D(nb_lines, vector<Complex>(nb_columns));
    Complex i = sqrt(-1);

    for ( int k = 0; k < nb_lines; k++) {
        for ( int l = 0; l < nb_columns; l++) {
            Complex F_k_l(0.0, 0.0); // F[k,l] with F the Discrete Fourier Transform
            for ( int nx = 0; nx < nb_lines; nx++) {
                for ( int ny = 0; ny < nb_columns; ny++) {
                    double angle = - 2 * i * M_PI * (nx * k / nb_lines + ny * l / nb_columns);
                    F_k_l += channel[nx][ny] * exp(angle);
                }
            }
            FFT2D[k][l] = F_k_l;
        }
    }

    return FFT2D;
}


vector<vector<double>> FastFourierModulus(FourierTransform FFT) {

    int nb_lines = FFT.size();
    int nb_columns = FFT[0].size();
    vector<vector<double>> modulus(nb_lines, vector<double> (nb_columns));

    for ( int k = 0; k < nb_lines; k++) {
        for ( int l = 0; l < nb_columns; l++) {
            modulus[k][l] = abs(FFT[k][l]);
        }
    }

    return modulus;
}


/*-------------------------------------------------------------------------
   Performs a 2D FFT inplace given a complex 2D array.
   The direction dir: 1 for forward, -1 for reverse.
   The size of the array (nx,ny).
   Return false if there are memory problems or the dimensions are not powers of 2.
*/

FourierTransform FastFourierTransform2D(Channel channel, int dir)
{
    int nx = channel.size();
    int ny = channel[0].size();
    int i,j;
    int m,twopm;
    double *real,*imag;

    FourierTransform FFT2D(nx,vector<Complex>(ny));
    FourierTransform CannotCompute(0, vector<Complex>(0));

    /* Transform the rows */
    real = (double *)malloc(nx * sizeof(double));
    imag = (double *)malloc(nx * sizeof(double));
    if (real == NULL || imag == NULL)
        return(CannotCompute);
    if (!Powerof2(nx,&m,&twopm) || twopm != nx)
        return(CannotCompute);
    for (j=0;j<ny;j++) {
        for (i=0;i<nx;i++) {
            real[i] = channel[i][j].real;
            imag[i] = channel[i][j].imag;
        }
        FFT(dir,m,real,imag);
        for (i=0;i<nx;i++) {
            FFT2D[i][j].real = real[i];
            FFT2D[i][j].imag = imag[i];
        }
    }
    free(real);
    free(imag);

    /* Transform the columns */
    real = (double *)malloc(ny * sizeof(double));
    imag = (double *)malloc(ny * sizeof(double));
    if (real == NULL || imag == NULL)
        return(CannotCompute);
    if (!Powerof2(ny,&m,&twopm) || twopm != ny)
        return(CannotCompute);
    for (i=0;i<nx;i++) {
        for (j=0;j<ny;j++) {
            real[j] = FFT2D[i][j].real;
            imag[j] = FFT2D[i][j].imag;
        }
        FFT(dir,m,real,imag);
        for (j=0;j<ny;j++) {
            FFT2D[i][j].real = real[j];
            FFT2D[i][j].imag = imag[j];
        }
    }
    free(real);
    free(imag);

    return(FFT2D);
}

/*-------------------------------------------------------------------------
   This computes an in-place complex-to-complex FFT
   x and y are the real and imaginary arrays of 2^m points.
   dir =  1 gives forward transform
   dir = -1 gives reverse transform

     Formula: forward
                  N-1
                  ---
              1   \          - j k 2 pi n / N
      X(n) = ---   >   x(k) e                    = forward transform
              N   /                                n=0..N-1
                  ---
                  k=0

      Formula: reverse
                  N-1
                  ---
                  \          j k 2 pi n / N
      X(n) =       >   x(k) e                    = forward transform
                  /                                n=0..N-1
                  ---
                  k=0
*/
int FFT(int dir,int m,double *x,double *y)
{
    long nn,i,i1,j,k,i2,l,l1,l2;
    double c1,c2,tx,ty,t1,t2,u1,u2,z;

    /* Calculate the number of points */
    nn = 1;
    for (i=0;i<m;i++)
        nn *= 2;

    /* Do the bit reversal */
    i2 = nn >> 1;
    j = 0;
    for (i=0;i<nn-1;i++) {
        if (i < j) {
            tx = x[i];
            ty = y[i];
            x[i] = x[j];
            y[i] = y[j];
            x[j] = tx;
            y[j] = ty;
        }
        k = i2;
        while (k <= j) {
            j -= k;
            k >>= 1;
        }
        j += k;
    }

    /* Compute the FFT */
    c1 = -1.0;
    c2 = 0.0;
    l2 = 1;
    for (l=0;l<m;l++) {
        l1 = l2;
        l2 <<= 1;
        u1 = 1.0;
        u2 = 0.0;
        for (j=0;j<l1;j++) {
            for (i=j;i<nn;i+=l2) {
                i1 = i + l1;
                t1 = u1 * x[i1] - u2 * y[i1];
                t2 = u1 * y[i1] + u2 * x[i1];
                x[i1] = x[i] - t1;
                y[i1] = y[i] - t2;
                x[i] += t1;
                y[i] += t2;
            }
            z =  u1 * c1 - u2 * c2;
            u2 = u1 * c2 + u2 * c1;
            u1 = z;
        }
        c2 = sqrt((1.0 - c1) / 2.0);
        if (dir == 1)
            c2 = -c2;
        c1 = sqrt((1.0 + c1) / 2.0);
    }

    /* Scaling for forward transform */
    if (dir == 1) {
        for (i=0;i<nn;i++) {
            x[i] /= (double)nn;
            y[i] /= (double)nn;
        }
    }

    return(TRUE);
}

/*-------------------------------------------------------------------------
   Calculate the closest but lower power of two of a number
   twopm = 2**m <= n
   Return TRUE if 2**m == n
*/
int Powerof2(int n,int *m,int *twopm)
{
    if (n <= 1) {
        *m = 0;
        *twopm = 1;
        return(FALSE);
    }

    *m = 1;
    *twopm = 2;
    do {
        (*m)++;
        (*twopm) *= 2;
    } while (2*(*twopm) <= n);

    if (*twopm != n)
        return(FALSE);
    else
        return(TRUE);
}

