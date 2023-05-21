#include <iostream>
#include <vector>
#include "sidesrc/matrix/csvreader.hpp"
#include "calculations.hpp"
#include "model.hpp"

std::vector<Matrix> train_test_split(Matrix data)
{
    std::vector<Matrix> result;
    data = mat_shuffle_row(data);
    Matrix x_data = mat_normalize(data.col_split(0, 4));
    Matrix y_data = mat_normalize(data.col_split(4, 5));
    y_data.show();
    Matrix x_data_test, y_data_test;
    for (int i = 0; i < data.rows() / 4; i++)
    {
        x_data_test.matrix_object.push_back(x_data.get_row(x_data.rows()-1));
        y_data_test.matrix_object.push_back(y_data.get_row(y_data.rows()-1));
        x_data.matrix_object.pop_back();
        y_data.matrix_object.pop_back();
    }
    result.push_back(x_data);
    result.push_back(y_data);
    result.push_back(x_data_test);
    result.push_back(y_data_test);
    return result;
}

int main()
{
    std::srand(std::time(0));
    // Data
    Matrix data = matrix_from_csv("/home/pedrozoz/repositories/cc-repo/cc-dummy/cc-mlp/src/iris.data");
    auto data_split = train_test_split(data);
    Matrix x_data = data_split[0], y_data = data_split[1], x_data_test = data_split[2], y_data_test = data_split[3];
    // Model
    MLP myMLP(&mean_squared_error, &mean_squared_error_prime, 0.0);
    myMLP.push_layer(Layer(4, &sigmoid, &sigmoid_prime));
    myMLP.push_layer(Layer(4, &sigmoid, &sigmoid_prime));
    myMLP.push_layer(Layer(1, &sigmoid, &sigmoid_prime));
    auto model = myMLP.compile();
    // Training
    std::vector<Matrix> x;
    std::vector<Matrix> y;
    for (int i = 0; i < x_data.rows(); i++)
    {
        x.push_back(Matrix(x_data.get_row(i)).transpose());
    }
    for (int i = 0; i < y_data.rows(); i++)
    {
        y.push_back(Matrix(y_data.get_row(i)).transpose());
    }
    model.fit(x, y, 100, 0.1L);
    for (int i = 0; i < y_data_test.rows(); i++)
    {
        model.feed_foward(Matrix(x_data_test.get_row(i)).transpose());
        std::cout << "Pred: " << model.activations[model.activations.size() - 1].get(0, 0) << " Real: " << y_data_test.get(i, 0) << "\n";
    }
    return 0;
}