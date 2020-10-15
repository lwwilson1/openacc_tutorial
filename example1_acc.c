#include <stdlib.h>

int main(int argc, char **argv)
{
    int num_elements = 1000;
    int *x = malloc(num_elements * sizeof(int));
    int *y = malloc(num_elements * sizeof(int));
    int *z = malloc(num_elements * sizeof(int));

    int a = 10;

    #pragma acc parallel loop
    for (int i = 0; i < num_elements; ++i) {
        x[i] = rand();
        y[i] = rand(); 
        z[i] = a * x[i] + y[i];
    }

    free(x);
    free(y);
    free(z);

    return 0;
}
