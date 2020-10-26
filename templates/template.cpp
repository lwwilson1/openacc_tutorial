#include <vector>

template <typename T> void daxpy(int N, T a, T* __restrict__ x,
                                 T* __restrict__ y);

using array_type = float;

int main(int argc, char** argv)
{
    int num_elements = 10000000;
    int num_iterations = 10000;

    std::vector<array_type> x(num_elements, 1.);
    std::vector<array_type> y(num_elements, 2.);

    for (int i = 0; i < num_iterations; ++i)
        daxpy <array_type> (num_elements, 10., x.data(), y.data());

    return 0;
}

template <typename T> void daxpy(int N, T a, T* __restrict__ x, 
                                 T* __restrict__ y)
{
    for (int i = 0; i < N; ++i) {
        y[i] = a * x[i] + y[i];
    }
}





