#include "model.hpp"
#include <vector>
#include "calculations.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

int in_vector(std::vector<double> vec, double value)
{
    for (int i = 0; i < vec.size(); i++)
    {
        
    }
}

doubleVMat from_csv(std::vector<int> other)
{
    std::string line_buffer, word_buffer;
    std::fstream csv_file("/home/pedrozoz/repositories/cc-repo/cc-mlp/iris.data");
    doubleVMat data;
    std::vector<std::string> encoding;
    std::vector<int> encoders;
    for (int i = 0; getline(csv_file, line_buffer); i++)
    {
        data.push_back(std::vector<double>());
        std::stringstream str(line_buffer);
        while (getline(str, word_buffer, ','))
        {
            
        }
    }
}

int main()
{
    MLP myMLP(&mean_squared_error, &mean_squared_error_prime, 0.0001);
    myMLP.push_layer(Layer(2, &sigmoid, &sigmoid_prime));
    myMLP.push_layer(Layer(3, &sigmoid, &sigmoid_prime));
    myMLP.push_layer(Layer(2, &sigmoid, &sigmoid_prime));
    Model myModel = myMLP.compile();
    doubleVMat layer_input = {{0}, {1}};
    std::cout << "Weights\n";
    print_matrix(myModel.weight_matrixes[0]);
    print_matrix(myModel.weight_matrixes[1]);
    // std::cout << "Activations\n";
    // print_matrix(myModel.activations[2]);
    // myModel.feed_foward(layer_input);
    // print_matrix(myModel.activations[2]);
    std::vector<doubleVMat> layer_train_x = {{{0}, {0}}, {{0}, {1}}, {{1}, {0}}, {{1}, {1}}};
    std::vector<doubleVMat> layer_train_y = {{{1}, {1}}, {{1}, {0}}, {{0}, {1}}, {{0}, {0}}};
    myModel.fit(layer_train_x, layer_train_y, 200, 0.0001);
    myModel.feed_foward({{0}, {0}});
    // print_matrix(myModel.activations[2]);
    myModel.feed_foward({{1}, {0}});
    // print_matrix(myModel.activations[2]);
    myModel.feed_foward({{0}, {1}});
    // print_matrix(myModel.activations[2]);
    myModel.feed_foward({{1}, {1}});
    // print_matrix(myModel.activations[2]);
}