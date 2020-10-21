#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
    double tol = 1e-5;
    int iter_max = 1000;
    int dim = 1000;

    double **A = malloc(dim * sizeof(double *));
    for (int i = 0; i < dim; ++i) A[i] = malloc(dim * sizeof(double));

    double **Anew = malloc(dim * sizeof(double *));
    for (int i = 0; i < dim; ++i) Anew[i] = malloc(dim * sizeof(double));

    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            A[i][j] = (double)rand() / (double)RAND_MAX;
        }
    }

    double err = 1.;
    int iter = 0;

    // Jacobi iteration
    #pragma acc data copy(A), create(Anew)
    while (err > tol && iter < iter_max) { 
        err = 0.0;
    
        #pragma acc parallel loop reduction(max:err)
        for (int i = 1; i < dim-1; ++i) { 
            for (int j = 1; j < dim-1; ++j) {
    
                Anew[i][j] = 0.25 * (A[i][j+1] + A[i][j-1] 
                                   + A[i-1][j] + A[i+1][j]);
    
                err = fmax(err, fabs(Anew[i][j] - A[i][j]));
            }
        }
    
        #pragma acc parallel loop
        for(int i = 1; i < dim-1; ++i) { 
            for(int j = 1; j < dim-1; ++j) {
               A[i][j] = Anew[i][j];
            }
        }
    
        iter++;

        printf("Iter %4d, error %e\n", iter, err);
    }

    for (int i = 0; i < dim; ++i) free(A[i]);
    free(A);

    for (int i = 0; i < dim; ++i) free(Anew[i]);
    free(Anew);
    
    return 0;
}
