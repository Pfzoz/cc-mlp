#ifndef MLP_MODEL
#define MLP_MODEL

#include <vector>
#include "structure.hpp"

class Model
{
private:
    // properties
    std::vector<doubleVMat> z_values;

public:
    // properties
    std::vector<doubleVMat(*)(doubleVMat)> activation_functions;
    std::vector<doubleVMat(*)(doubleVMat)> activation_primes;
    std::vector<doubleVMat> weight_matrixes;
    std::vector<doubleVMat> bias_matrixes;
    std::vector<doubleVMat> activations;
    double (*loss_metric)(doubleVMat, doubleVMat);
    doubleVMat (*loss_prime)(doubleVMat, doubleVMat);
    double regularization_term;

    // constructors
    Model(){};
    ~Model(){};

    // methods

    void feed_foward(doubleVMat x)
    {
        if (x.size() != this->activations[0].size())
        {
            std::cout << "Wrong shape towards specified architecture's shape\n";
            exit(1);
        }
        else
        {
            this->activations[0] = x;
            this->z_values.push_back(x);
            for (int i = 0; i < this->activations.size()-1; i++)
            {
                doubleVMat z_value = matsum(matmul(this->weight_matrixes[i], this->activations[i]), this->bias_matrixes[i]);
                doubleVMat activation = this->activation_functions[i](z_value);
                this->activations[i+1] = activation;
                this->z_values.push_back(z_value);
            }
        }
    }

    void back_propagate(doubleVMat y, double learning_rate)
    {
        doubleVMat loss_der = this->loss_prime(this->activations[this->activations.size()-1], y);
        doubleVMat regularized_loss = scalardot(scalarsum(loss_der, this->regularization_term), matsummation(this->weight_matrixes));
        doubleVMat delta = matdot(regularized_loss, this->activation_primes[this->activation_primes.size()-1](this->activations[this->activations.size()-1]));
        for (int i = this->weight_matrixes.size()-1; i > -1; i--)
        {
            
            this->bias_matrixes[i] = matsum(this->bias_matrixes[i], scalardot(delta, learning_rate));
            this->weight_matrixes[i] = matsum(this->weight_matrixes[i], matmul(delta, transpose(this->activations[i])));
            doubleVMat z_value = z_values[i];
            doubleVMat sp = this->activation_primes[i](z_value);
            delta = matdot(matmul(transpose(this->weight_matrixes[i]), delta), sp);
        }
    }

    void fit(std::vector<doubleVMat> x, std::vector<doubleVMat> y, int epochs = 100, double learning_rate = 0.0001)
    {
        for (int i = 0; i < epochs; i++)
        {
            double main_error = 0;
            for (int j = 0; j < x.size(); j++)
            {
                this->feed_foward(x[j]);
                main_error += this->loss_metric(this->activations[this->activations.size()-1], y[j]);
                this->back_propagate(y[j], learning_rate);
            }
            std::cout << "Epoch: " << i << " MSE: " << main_error/y.size() << '\n';
        }
    }


};

class MLP
{
public:
    // properties
    std::vector<Layer> layers;
    double (*loss_metric)(doubleVMat, doubleVMat);
    doubleVMat (*loss_prime)(doubleVMat, doubleVMat);
    double regularization_term;

    // constructors
    MLP(){}
    ~MLP(){}

    MLP(double(*loss_metric)(doubleVMat, doubleVMat), doubleVMat(*loss_prime)(doubleVMat, doubleVMat), double regularization_term = 0.01)
    {
        this->loss_metric = loss_metric;
        this->loss_prime = loss_prime;
        this->regularization_term = regularization_term;
    }

    // methods

    void push_layer(Layer layer)
    {
        this->layers.push_back(layer);
    }

    Model compile()
    {
        Model model;
        model.loss_metric = this->loss_metric;
        model.loss_prime = this->loss_prime;
        for (int i = 0; i < this->layers.size(); i++)
        {
            model.activations.push_back(this->layers[i].compile_activations());
            if (i != 0)
            {   
                model.activation_functions.push_back(this->layers[i].activation_function);
                model.activation_primes.push_back(this->layers[i].activation_prime);
                model.bias_matrixes.push_back(this->layers[i].compile_biases());
            }
            if (i != this->layers.size()-1)
            {
                model.weight_matrixes.push_back(this->layers[i].compile_weights(this->layers[i+1]));
            }
        }
        return model;
    }
};

#endif