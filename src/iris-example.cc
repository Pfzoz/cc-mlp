#include <iostream>
#include <vector>
#include "sidesrc/matrix/csvreader.hpp"
#include "calculations.hpp"
#include "model.hpp"

Matrix mat_shuffle_row(Matrix matrix)
{
    Matrix result;
    int original_size = matrix.rows();
    while (result.rows() != original_size)
    {
        int choice = std::rand() % matrix.rows();
        result.matrix_object.push_back(matrix.get_row(choice));
        matrix.matrix_object.erase(matrix.matrix_object.begin() + choice);
    }
    return result;
}



int main()
{
    std::srand(std::time(0));
    // Data
    Matrix data = matrix_from_csv("/home/pedrozoz/repositories/cc-repo/cc-dummy/cc-mlp/src/iris.data");
    std::cout << "Normalized Data:\n";
    data = mat_normalize_cols(data);
    data.show();
    data = mat_shuffle_row(data);
    Matrix test_data;
    for (int i = 0; i < data.rows() / 5; i++)
    {
        test_data.matrix_object.push_back(data.get_row(data.rows()-1));
        data.matrix_object.pop_back();
    }
    std::cout << "Train Data:\n";
    data.show();
    std::cout << "Test Data:\n";
    test_data.show();
    // Model
    MLP myMLP(&mean_squared_error, &mean_squared_error_prime, 0.0L);
    myMLP.push_layer(Layer(4, &sigmoid, &sigmoid_prime));
    myMLP.push_layer(Layer(4, &sigmoid, &sigmoid_prime));
    myMLP.push_layer(Layer(1, &sigmoid, &sigmoid_prime));
    auto model = myMLP.compile();
    // Training
    Matrix x_data = data.col_split(0, 4);
    Matrix y_data = data.col_split(4, 5);
    Matrix x_data_test = test_data.col_split(0, 4);
    Matrix y_data_test = test_data.col_split(4, 5);
    std::vector<Matrix> x;
    std::vector<Matrix> y;
    std::vector<Matrix> x_test;
    std::vector<Matrix> y_test;
    for (int i = 0; i < x_data.rows(); i++)
    {
        Matrix x_mat = Matrix(4, 1);
        for (int j = 0; j < 4; j++)
        {
            x_mat.set(j, 0, x_data.get(i, j));
        }
        x.push_back(x_mat);
    }
    for (int i = 0; i < y_data.rows(); i++)
    {
        Matrix y_mat = Matrix(1, 1);
        for (int j = 0; j < 1; j++)
        {
            y_mat.set(j, 0, y_data.get(i, j));
        }
        y.push_back(y_mat);
    }
    model.fit(x, y, 100, 0.1L);
    for (int i = 0; i < y_data_test.rows(); i++)
    {
        Matrix test_mat = Matrix(4, 1);
        for (int j = 0; j < 4; j++)
        {
            test_mat.set(j, 0, x_data_test.get(i, j));
        }
        model.feed_foward(test_mat);
        std::cout << "Pred: " << model.activations[model.activations.size()-1].get(0, 0) << " Real: " << y_data_test.get(i, 0) << "\n";
    }
    return 0;
}