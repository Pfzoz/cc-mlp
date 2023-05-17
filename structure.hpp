#ifndef MLP_STRUCTURE
#define MLP_STRUCTURE

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "matrix.hpp"

#define doubleVMat std::vector<std::vector<double>>

class Layer
{
public:
    // properties
    Matrix (*activation_function)(Matrix);
    Matrix (*activation_prime)(Matrix);
    int neurons;
    // constructors
    Layer(){};
    ~Layer(){};

    // methods
    Layer(int neurons, Matrix (*activation_function)(Matrix), Matrix (*activation_prime)(Matrix))
    {
        this->activation_function = activation_function;
        this->activation_prime = activation_prime;
        this->neurons = neurons;
    }

    void set_neurons(int neurons)
    {
        this->neurons = neurons;
    }

    Matrix compile_weights(Layer __o)
    {
        int rows = __o.neurons, columns = this->neurons;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator(seed);
        std::normal_distribution<long double> distribution(0.0, 1.0);
        Matrix weights(rows, columns);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                weights.set(i, j, distribution(generator));
            }
        }
        return weights;
    }

    Matrix compile_activations()
    {
        return Matrix(this->neurons, 1);
    }

    Matrix compile_biases()
    {
        return Matrix(this->neurons, 1);
    }
};

#endif