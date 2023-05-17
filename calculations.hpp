#ifndef CALCULATIONS
#define CALCULATIONS

#include <vector>
#include <cmath>
#include "matrix.hpp"

Matrix clip(Matrix x, int max, int min)
{
    for (int i = 0; i < x.matrix_object.size(); i++)
    {
        for (int j = 0; j < x.matrix_object[0].size(); j++)
        {
            if (x.matrix_object[i][j] > max)
            {
                x.matrix_object[i][j] = max;
            }
            else if (x.matrix_object[i][j] < min)
            {
                x.matrix_object[i][j] = min;
            }
        }
    }
    return x;
}

Matrix relu(Matrix x)
{
    return (x < 0) * x;
}

Matrix relu_prime(Matrix x)
{
    return (x > 0) * 1;
}

long double matsummation(std::vector<Matrix> x)
{
    long double accum = 0;
    for (int i = 0; i < x.size(); i++)
    {
        accum += x[i].sum();
    }
    return accum;
}

Matrix mean_squared_error_prime(Matrix estimated_y, Matrix y)
{
    return ((y - estimated_y) * -2) / (estimated_y.matrix_object.size() * estimated_y.matrix_object[0].size());
}

long double mean_squared_error(Matrix estimated_y, Matrix y)
{
    return ((estimated_y - y).pow(2)).mean();
}

Matrix sigmoid(Matrix x)
{
    x = clip(x, 30, -30);

    for (int i = 0; i < x.matrix_object.size(); i++)
    {
        for (int j = 0; j < x.matrix_object[0].size(); j++)
        {
            x.matrix_object[i][j] = 1.0 / (1.0 + (pow(exp(1.0), x.matrix_object[i][j])));
        }
    }

    return x;
}

Matrix sigmoid_prime(Matrix x)
{
    x = clip(x, 30, -30);
    return x * ((x * -1) + 1);
}

#endif