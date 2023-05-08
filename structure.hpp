#ifndef MLP_STRUCTURE
#define MLP_STRUCTURE

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "calculations.hpp"

#define doubleVMat std::vector<std::vector<double>>

class Layer
{
public:
    // properties
    doubleVMat (*activation_function)(doubleVMat);
    doubleVMat (*activation_prime)(doubleVMat);
    int neurons;
    // constructors
    Layer(){};
    ~Layer(){};

    // methods
    Layer(int neurons, doubleVMat (*activation_function)(doubleVMat), doubleVMat (*activation_prime)(doubleVMat))
    {
        this->activation_function = activation_function;
        this->activation_prime = activation_prime;
        this->neurons = neurons;
    }

    void set_neurons(int neurons)
    {
        this->neurons = neurons;
    }

    doubleVMat compile_weights(Layer __o)
    {
        int rows = __o.neurons, columns = this->neurons;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator(seed);
        std::normal_distribution<double> distribution(0.0, 1.0);
        std::vector<double> column(columns, 0);
        std::vector<std::vector<double>> w(rows, column);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                w[i][j] = distribution(generator);
            }
        }
        return w;
    }

    doubleVMat compile_activations()
    {
        std::vector<double> single_row(1);
        doubleVMat activations(this->neurons, single_row);
        return activations;
    }

    doubleVMat compile_biases()
    {
        std::vector<double> single_row(1, 0);
        doubleVMat biases(this->neurons, single_row);
        return biases;
    }
};

void print_matrix(doubleVMat x)
{
    std::cout << '[' << ' ';
    for (int i = 0; i < x.size(); i++)
    {  
        for (int j = 0; j < x[0].size(); j++)
        {
            std::cout << x[i][j] << ' ';
        }
        std::cout <<'\n';
    }
    std::cout << " ]";
}

#endif