#include <vector>
#include <string>
#include "calculations.hpp"
#include "matrix.hpp"
#include "model.hpp"

int main()
{
    MLP myMLP(&mean_squared_error, &mean_squared_error_prime, 0);
    myMLP.push_layer(Layer(2, &sigmoid, &sigmoid_prime));
    myMLP.push_layer(Layer(3, &sigmoid, &sigmoid_prime));
    myMLP.push_layer(Layer(2, &sigmoid, &sigmoid_prime));
    Model myModel = myMLP.compile();
    myModel.activations[1].show();
    Matrix layer_input(2, 1);
    layer_input.set(1, 0, 1);
    std::cout << "Weights 1\n";
    myModel.weight_matrixes[0].show();
    std::cout << "Weights 2\n";
    myModel.weight_matrixes[1].show();
    std::cout << "Activations\n";
    myModel.feed_foward(layer_input);
    myModel.activations[2].show();
    std::vector<Matrix> layer_train_x(4, Matrix(2, 1));
    layer_train_x[1].set(1, 0, 1);
    layer_train_x[2].set(0, 0, 1);
    layer_train_x[3].set(0, 0, 1);
    layer_train_x[3].set(1, 0, 1);
    std::vector<Matrix> layer_train_y(4, Matrix(2, 1));
    layer_train_y[0].set(0, 0, 1);
    layer_train_y[0].set(1, 0, 1);
    layer_train_y[1].set(0, 0, 1);
    layer_train_y[2].set(1, 0, 1);
    std::cout << "Training\n";
    myModel.fit(layer_train_x, layer_train_y, 200, 1);
    myModel.feed_foward(Matrix(2, 1));
    myModel.activations[2].show();
    myModel.feed_foward(Matrix(2, 1, 1));
    myModel.activations[2].show();
}