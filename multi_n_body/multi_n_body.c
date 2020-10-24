#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void copy_array_into_device(double * restrict x, int dim);

void compute_potential(double * restrict x, double * restrict y,
        double * restrict z, double * restrict q,
        double * restrict potential, int dim, double alpha);

double pot_fun(double dx, double dy, double dz, double q, double alpha);

int main(int argc, char **argv)
{
    int dim = 10000;
    int num_potentials = 100;

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

    for (int i = 0; i < num_potentials; ++i) {
        double alpha = (double)rand() / (double)RAND_MAX;
        compute_potential(x, y, z, q, potential, dim, alpha);
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

void compute_potential(double * restrict x, double * restrict y,
                       double * restrict z, double * restrict q,
                       double * restrict potential, int dim,
                       double alpha)
{
    for (int i = 0; i < dim; ++i) { 
        for (int j = 0; j < dim; ++j) {
            if (i != j) {
                double dx = x[i] - x[j];
                double dy = y[i] - y[j];
                double dz = z[i] - z[j];
                
                potential[i] += pot_fun(dx, dy, dz, q[j], alpha);
            }
        }
    }
}


double pot_fun(double dx, double dy, double dz, 
               double q, double alpha)
{
    double radius = sqrt(dx*dx + dy*dy + dz*dz);
    return exp(-alpha * radius) / radius;
}
