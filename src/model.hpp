#ifndef MLP_MODEL
#define MLP_MODEL

#include <vector>
#include "structure.hpp"

class Model
{
private:
    // properties
    std::vector<Matrix> z_values;

public:
    // properties
    std::vector<Matrix (*)(Matrix)> activation_functions;
    std::vector<Matrix (*)(Matrix)> activation_primes;
    std::vector<Matrix> weight_matrixes;
    std::vector<Matrix> bias_matrixes;
    std::vector<Matrix> activations;
    long double (*loss_metric)(Matrix, Matrix);
    Matrix (*loss_prime)(Matrix, Matrix);
    long double regularization_term;

    // constructors
    Model(){};
    ~Model(){};

    // methods

    void feed_foward(Matrix x)
    {
        this->z_values.clear();
        this->activations[0] = x;
        this->z_values.push_back(x);
        for (int i = 0; i < this->activations.size() - 1; i++)
        {
            Matrix z_value = this->weight_matrixes[i].matmul(this->activations[i])+this->bias_matrixes[i];
            Matrix activation = this->activation_functions[i](z_value);
            this->activations[i + 1] = activation;
            this->z_values.push_back(z_value);
        }
    }

    void back_propagate(Matrix y, long double learning_rate)
    {
        Matrix loss_derivative = this->loss_prime(y, this->activations[this->activations.size()-1]);
        long double reg = this->weight_matrixes[this->weight_matrixes.size()-1].sum()*this->regularization_term;
        // std::cout << "REG:" << reg << ";\n";
        Matrix cost = loss_derivative+reg;
        Matrix delta = cost*this->activation_primes[this->activation_primes.size()-1](this->activations[this->activations.size()-1]);
        for (int i = this->weight_matrixes.size() - 1; i > -1; i--)
        {
            this->bias_matrixes[i] -= delta*learning_rate;
            this->weight_matrixes[i] -= delta.matmul(this->activations[i].transpose())*learning_rate;
            Matrix z_value = z_values[i];
            Matrix sp = this->activation_primes[i](z_value);
            delta = (this->weight_matrixes[i].transpose().matmul(delta))*sp;
        }
    }

    void fit(std::vector<Matrix> x, std::vector<Matrix> y, int epochs = 100, long double learning_rate = 0.0001)
    {
        for (int i = 0; i < epochs; i++)
        {
            long double main_error = 0;
            for (int j = 0; j < x.size(); j++)
            {
                this->feed_foward(x[j]);
                main_error += this->loss_metric(this->activations[this->activations.size() - 1], y[j]);
                this->back_propagate(y[j], learning_rate);
            }
            std::cout << "Epoch: " << i << " MSE: " << main_error / y.size() << '\n';
        }
    }
};

class MLP
{
public:
    // properties
    std::vector<Layer> layers;
    long double (*loss_metric)(Matrix, Matrix);
    Matrix (*loss_prime)(Matrix, Matrix);
    long double regularization_term;

    // constructors
    MLP() {}
    ~MLP() {}

    MLP(long double (*loss_metric)(Matrix, Matrix), Matrix (*loss_prime)(Matrix, Matrix), long double regularization_term = 0.01)
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
            if (i != this->layers.size() - 1)
            {
                model.weight_matrixes.push_back(this->layers[i].compile_weights(this->layers[i + 1]));
            }
        }
        return model;
    }
};

#endif