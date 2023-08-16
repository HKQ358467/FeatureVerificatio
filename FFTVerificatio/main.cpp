#include <complex.h>
#include <math.h>

#define PI 3.14159265358979323846

void fft_radix(complex double* a, int n) {
    if (n == 1)
        return;

    complex double a0[n/2];
    complex double a1[n/2];
    for (int i = 0; i < n/2; i++) {
        a0[i] = a[i*2];
        a1[i] = a[i*2+1];
    }

    fft_radix(a0, n/2);
    fft_radix(a1, n/2);

    for (int i = 0; i < n/2; i++) {
        complex double t = cexp(-2.0*I*PI*i/n) * a1[i];
        a[i] = a0[i] + t;
        a[i+n/2] = a0[i] - t;
    }
}

void fft_mixed_radix(complex double* a, int n, int radix) {
    if (n == radix) {
        fft_radix(a, n);
        return;
    }

    int m = n / radix;
    for (int i = 0; i < radix; i++) {
        fft_mixed_radix(a + i*m, m, radix);
    }

    for (int i = 0; i < n; i++) {
        complex double t = 0;
        for (int j = 0; j < radix; j++) {
            t += cexp(-2.0*I*PI*i*j/radix) * a[j*m + i%radix];
        }
        a[i] = t;
    }
}

int main() {
    
    int n = 16384; 
    int radix = 2; 
    complex double* a = (complex double*) malloc(n * sizeof(complex double));
    
    
    for (int i = 0; i < n; i++) {
        a[i] = cos(2 * PI * i / n);
    }
    
    
    clock_t start = clock();
    fft_mixed_radix(a, n, radix);
    clock_t end = clock();
    
    
    double time_taken = ((double) end - start) / CLOCKS_PER_SEC;
    
    printf("Time taken by fft_mixed_radix: %f seconds\n", time_taken);
    
    free(a);
    
    return 0;
}