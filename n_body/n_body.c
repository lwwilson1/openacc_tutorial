#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
    int dim = 100000;

    double * restrict x = malloc(dim * sizeof(double));
    double * restrict y = malloc(dim * sizeof(double));
    double * restrict z = malloc(dim * sizeof(double));
    double * restrict q = malloc(dim * sizeof(double));
    double * restrict potential = malloc(dim * sizeof(double));

    for (int i = 0; i < dim; ++i) {
        x[i] = (double)rand() / (double)RAND_MAX;
        y[i] = (double)rand() / (double)RAND_MAX;
        z[i] = (double)rand() / (double)RAND_MAX;
        q[i] = (double)rand() / (double)RAND_MAX;
        potential[i] = 0.;
    }

    for (int i = 0; i < dim; ++i) { 
        for (int j = 0; j < dim; ++j) {
            if (i != j) {
                double dx = x[i] - x[j];
                double dy = y[i] - y[j];
                double dz = z[i] - z[j];
                double radius = sqrt(dx*dx + dy*dy + dz*dz);
                
                potential[i] += q[j] / radius;
            }
        }
    }

    double total_potential = 0.;
    for (int i = 0; i < dim; ++i) total_potential += potential[i];
    printf("Total potential is: %f\n", total_potential);
    
    free(x);
    free(y);
    free(z);
    free(q);
    free(potential);
    
    return 0;
}
