#include <stdlib.h>

int main(int argc, char **argv)
{
    int num_elements = 1000000;
    double * restrict x = malloc(num_elements * sizeof(double));
    double * restrict y = malloc(num_elements * sizeof(double));

    int a = 10.;

    #pragma acc kernels
    { 
        for (int i = 0; i < num_elements; ++i) {
            x[i] = 1.;
            y[i] = 2.; 
        }

        for (int i = 0; i < num_elements; ++i) {
            y[i] = a * x[i] + y[i];
        }
    }

    free(x);
    free(y);

    return 0;
}
