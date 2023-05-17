#include <iostream>
#include "csvreader.hpp"
#include "calculations.hpp"
#include "model.hpp"

int main()
{
    Matrix data = matrix_from_csv("/home/pedrozoz/repositories/cc-repo/cc-dummy/cc-mlp/iris.data");
    std::cout << "Encoded Data:\n";
    data.show();
    std::cout << "Normalized Data:\n";
    data = mat_normalize_cols(data);
    data.show();
    return 0;
}