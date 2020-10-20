#include <stdlib.h>

void daxpy(int N, double a, double *x, restrict double *y);

int main(int argc, char **argv)
{
    int num_elements = 1000000;
    double *x = malloc(num_elements * sizeof(double));
    double *y = malloc(num_elements * sizeof(double));

    #pragma acc parallel loop
    for (int i = 0; i < num_elements; ++i) {
        x[i] = 1.;
        y[i] = 2.; 
    }

    daxpy(num_elements, 10., x, y);

    free(x);
    free(y);

    return 0;
}


void daxpy(int N, double a, double *x, restrict double *y)
{
    #pragma acc parallel loop
    for (int i = 0; i < N; ++i) {
        y[i] = a * x[i] + y[i];
    }
}






