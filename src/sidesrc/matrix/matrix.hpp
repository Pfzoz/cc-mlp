#ifndef MATRIX
#define MATRIX

#include <iostream>
#include <vector>
#include <cmath>

std::vector<std::vector<long double>> _generate_matrix(int rows, int cols, long double default_value)
{
    std::vector<long double> single_row(cols, default_value);
    return std::vector<std::vector<long double>>(rows, single_row);
}

class Matrix
{
public:
    std::vector<std::vector<long double>> matrix_object;
    Matrix(){};
    ~Matrix(){};
    Matrix(int rows, int cols, long double default_value = 0)
    {
        this->matrix_object = _generate_matrix(rows, cols, default_value);
    }

    // Logic Operations
    Matrix operator<(long double __o);
    Matrix operator>(long double __o);

    // Scalar Operations
    Matrix operator+=(long double __o);
    Matrix operator-=(long double __o);
    Matrix operator*=(long double __o);
    Matrix operator/=(long double __o);
    Matrix operator+(long double __o);
    Matrix operator-(long double __o);
    Matrix operator*(long double __o);
    Matrix operator/(long double __o);
    Matrix pow(long double __o);

    // Matrix Operations
    Matrix operator+=(Matrix __o);
    Matrix operator-=(Matrix __o);
    Matrix operator*=(Matrix __o);
    Matrix operator/=(Matrix __o);
    Matrix operator+(Matrix __o);
    Matrix operator-(Matrix __o);
    Matrix operator*(Matrix __o);
    Matrix operator/(Matrix __o);

    // Algebraic Methods

    Matrix transpose();
    Matrix matmul(Matrix __o);
    long double sum();
    long double mean();

    // Getters/Setters

    long double get(int row, int col)
    {
        return this->matrix_object[row][col];
    }

    void set(int row, int col, long double x)
    {
        this->matrix_object[row][col] = x;
    }

    std::vector<long double> get_row(int row)
    {
        return this->matrix_object[row];
    }

    std::vector<long double> get_col(int col)
    {
        std::vector<long double> column;
        for (int i = 0; i < this->matrix_object.size(); i++)
        {
            column.push_back(this->matrix_object[i][col]);
        }
        return column;
    }

    Matrix row_split(int begin, int end)
    {
        Matrix result = (*this);
        int rows = result.rows();
        for (int i = 0; i < rows-end; i++)
        {
            result.matrix_object.pop_back();
        }
        for (int i = 0; i < begin; i++)
        {
            result.matrix_object.erase(result.matrix_object.begin()+0);
        }
        return result;
    }

    Matrix col_split(int begin, int end)
    {
        Matrix result = (*this);
        int cols = result.cols();
        for (int i = 0; i < result.rows(); i++)
        {
            for (int j = 0; j < cols-end; j++)
            {
                result.matrix_object[i].pop_back();
            }
            for (int j = 0; j < begin; j++)
            {
                result.matrix_object[i].erase(result.matrix_object[i].begin()+0);
            }
        }
        return result;
    }

    int rows()
    {
        return this->matrix_object.size();
    }

    int cols()
    {
        return this->matrix_object[0].size();
    }

    // Other Methods

    void show()
    {
        for (int i = 0; i < this->matrix_object.size(); i++)
        {
            for (int j = 0; j < this->matrix_object[0].size(); j++)
            {
                std::cout << this->matrix_object[i][j] << " ";
            }
            std::cout << '\n';
        }
    }

    long double col_max(int col)
    {
        long double maximum = this->matrix_object[0][col];
        for (int i = 1; i < this->rows(); i++)
        {
            if (maximum < this->matrix_object[i][col])
            {
                maximum = this->matrix_object[i][col];
            }
        }
        return maximum;
    }

    long double col_min(int col)
    {
        long double minimum = this->matrix_object[0][col];
        for (int i = 1; i < this->rows(); i++)
        {
            if (minimum > this->matrix_object[i][col])
            {
                minimum = this->matrix_object[i][col];
            }
        }
        return minimum;
    }

    long double max()
    {
        long double maximum = this->col_max(0);
        for (int i = 1; i < this->cols(); i++)
        {
            if (maximum < this->col_max(i))
            {
                maximum = this->col_max(i);
            }
        }
        return maximum;
    }

    long double min()
    {
        long double minimum = this->col_min(0);
        for (int i = 1; i < this->cols(); i++)
        {
            if (minimum > this->col_min(i))
            {
                minimum = this->col_min(i);
            }
        }
        return minimum;
    }
};

// Logic Operations
/// Not-In-Place
Matrix Matrix::operator<(long double __o)
{
    Matrix res = (*this);
    for (int i = 0; i < this->matrix_object.size(); i++)
    {
        for (int j = 0; j < this->matrix_object[0].size(); j++)
        {
            res.matrix_object[i][j] = res.matrix_object[i][j] < __o;
        }
    }
    return res;
}

Matrix Matrix::operator>(long double __o)
{
    Matrix res = (*this);
    for (int i = 0; i < this->matrix_object.size(); i++)
    {
        for (int j = 0; j < this->matrix_object[0].size(); j++)
        {
            res.matrix_object[i][j] = res.matrix_object[i][j] > __o;
        }
    }
    return res;
}

// Scalar Operations
/// In-Place
Matrix Matrix::operator+=(long double __o)
{
    for (int i = 0; i < this->matrix_object.size(); i++)
    {
        for (int j = 0; j < this->matrix_object[0].size(); j++)
        {
            this->matrix_object[i][j] += __o;
        }
    }
    return (*this);
}

Matrix Matrix::operator-=(long double __o)
{
    for (int i = 0; i < this->matrix_object.size(); i++)
    {
        for (int j = 0; j < this->matrix_object[0].size(); j++)
        {
            this->matrix_object[i][j] -= __o;
        }
    }
    return (*this);
}

Matrix Matrix::operator*=(long double __o)
{
    for (int i = 0; i < this->matrix_object.size(); i++)
    {
        for (int j = 0; j < this->matrix_object[0].size(); j++)
        {
            this->matrix_object[i][j] *= __o;
        }
    }
    return (*this);
}

Matrix Matrix::operator/=(long double __o)
{
    for (int i = 0; i < this->matrix_object.size(); i++)
    {
        for (int j = 0; j < this->matrix_object[0].size(); j++)
        {
            this->matrix_object[i][j] /= __o;
        }
    }
    return (*this);
}
/// Not-In-Place
Matrix Matrix::operator+(long double __o)
{
    Matrix res = (*this);
    for (int i = 0; i < this->matrix_object.size(); i++)
    {
        for (int j = 0; j < this->matrix_object[0].size(); j++)
        {
            res.matrix_object[i][j] += __o;
        }
    }
    return res;
}

Matrix Matrix::operator-(long double __o)
{
    Matrix res = (*this);
    for (int i = 0; i < this->matrix_object.size(); i++)
    {
        for (int j = 0; j < this->matrix_object[0].size(); j++)
        {
            res.matrix_object[i][j] -= __o;
        }
    }
    return res;
}

Matrix Matrix::operator*(long double __o)
{
    Matrix res = (*this);
    for (int i = 0; i < this->matrix_object.size(); i++)
    {
        for (int j = 0; j < this->matrix_object[0].size(); j++)
        {
            res.matrix_object[i][j] *= __o;
        }
    }
    return res;
}

Matrix Matrix::operator/(long double __o)
{
    Matrix res = (*this);
    for (int i = 0; i < this->matrix_object.size(); i++)
    {
        for (int j = 0; j < this->matrix_object[0].size(); j++)
        {
            res.matrix_object[i][j] /= __o;
        }
    }
    return res;
}

Matrix Matrix::pow(long double __o)
{
    Matrix res = (*this);
    for (int i = 0; i < this->matrix_object.size(); i++)
    {
        for (int j = 0; j < this->matrix_object[0].size(); j++)
        {
            res.matrix_object[i][j] = std::pow(res.matrix_object[i][j], __o);
        }
    }
    return res;
}

// Matrix Operations
/// In-Place
Matrix Matrix::operator+=(Matrix __o)
{
    for (int i = 0; i < this->matrix_object.size(); i++)
    {
        for (int j = 0; j < this->matrix_object[0].size(); j++)
        {
            this->matrix_object[i][j] += __o.matrix_object[i][j];
        }
    }
    return (*this);
}

Matrix Matrix::operator-=(Matrix __o)
{
    for (int i = 0; i < this->matrix_object.size(); i++)
    {
        for (int j = 0; j < this->matrix_object[0].size(); j++)
        {
            this->matrix_object[i][j] -= __o.matrix_object[i][j];
        }
    }
    return (*this);
}

Matrix Matrix::operator*=(Matrix __o)
{
    for (int i = 0; i < this->matrix_object.size(); i++)
    {
        for (int j = 0; j < this->matrix_object[0].size(); j++)
        {
            this->matrix_object[i][j] *= __o.matrix_object[i][j];
        }
    }
    return (*this);
}

Matrix Matrix::operator/=(Matrix __o)
{
    for (int i = 0; i < this->matrix_object.size(); i++)
    {
        for (int j = 0; j < this->matrix_object[0].size(); j++)
        {
            this->matrix_object[i][j] /= __o.matrix_object[i][j];
        }
    }
    return (*this);
}
/// Not-In-Place
Matrix Matrix::operator+(Matrix __o)
{
    Matrix res = (*this);
    for (int i = 0; i < this->matrix_object.size(); i++)
    {
        for (int j = 0; j < this->matrix_object[0].size(); j++)
        {
            res.matrix_object[i][j] += __o.matrix_object[i][j];
        }
    }
    return res;
}

Matrix Matrix::operator-(Matrix __o)
{
    Matrix res = (*this);
    for (int i = 0; i < this->matrix_object.size(); i++)
    {
        for (int j = 0; j < this->matrix_object[0].size(); j++)
        {
            res.matrix_object[i][j] -= __o.matrix_object[i][j];
        }
    }
    return res;
}

Matrix Matrix::operator*(Matrix __o)
{
    Matrix res = (*this);
    for (int i = 0; i < this->matrix_object.size(); i++)
    {
        for (int j = 0; j < this->matrix_object[0].size(); j++)
        {
            res.matrix_object[i][j] *= __o.matrix_object[i][j];
        }
    }
    return res;
}

Matrix Matrix::operator/(Matrix __o)
{
    Matrix res = (*this);
    for (int i = 0; i < this->matrix_object.size(); i++)
    {
        for (int j = 0; j < this->matrix_object[0].size(); j++)
        {
            res.matrix_object[i][j] /= __o.matrix_object[i][j];
        }
    }
    return res;
}

/// Algebraic Operations

Matrix Matrix::transpose()
{

    Matrix res(this->matrix_object[0].size(), this->matrix_object.size());
    for (int i = 0; i < res.matrix_object.size(); i++)
    {
        for (int j = 0; j < res.matrix_object[0].size(); j++)
        {
            res.matrix_object[i][j] = this->matrix_object[j][i];
        }
    }
    return res;
}

Matrix Matrix::matmul(Matrix __o)
{
    Matrix res(this->matrix_object.size(), __o.matrix_object[0].size());
    Matrix y = __o.transpose();
    for (int i = 0; i < this->matrix_object.size(); i++)
    {
        for (int j = 0; j < __o.matrix_object[0].size(); j++)
        {
            long double accum = 0;
            for (int k = 0; k < y.matrix_object[0].size(); k++)
            {
                accum += this->matrix_object[i][k] * y.matrix_object[j][k];
            }
            res.matrix_object[i][j] = accum;
        }
    }
    return res;
}

long double Matrix::sum()
{
    long double accum = 0;
    for (int i = 0; i < this->matrix_object.size(); i++)
    {
        for (int j = 0; j < this->matrix_object[0].size(); j++)
        {
            accum += this->matrix_object[i][j];
        }
    }
    return accum;
}

long double Matrix::mean()
{
    return this->sum() / (this->matrix_object.size() * this->matrix_object[0].size());
}

// Matrix-Wise Functions

Matrix mat_normalize(Matrix matrix)
{
    long double min = matrix.min(), max = matrix.max();
    std::cout << "MAX: " << max << " MIN: " << min << '\n'; 
    for (int i = 0; i < matrix.cols(); i++)
    {
        for (int j = 0; j < matrix.rows(); j++)
        {
            long double new_value = (matrix.get(j, i)-min)/(max-min);
            matrix.set(j, i, new_value);
        }
    }
    return matrix;
}

#endif