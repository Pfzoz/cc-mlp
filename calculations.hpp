#ifndef CALCULATIONS
#define CALCULATIONS

#include <vector>
#include <cmath>
#define doubleVMat std::vector<std::vector<double>>

doubleVMat relu(doubleVMat x)
{
    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < x[0].size(); j++)
        {
            if (x[i][j] <= 0)
                x[i][j] = 0;
        }
    }
    return x;
}

doubleVMat relu_prime(doubleVMat x)
{
    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < x[0].size(); j++)
        {
            if (x[i][j] <= 0)
                x[i][j] = 0;
            else
                x[i][j] = 1;
        }
    }
    return x;
}

doubleVMat scalardot(doubleVMat x, double scalar)
{
    doubleVMat result(x.size(), std::vector<double>(x[0].size()));
    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < x[0].size(); j++)
        {
            result[i][j] = x[i][j]*scalar;
        }
    }
    return result;
}

doubleVMat scalarsum(doubleVMat x, double scalar)
{
    doubleVMat result(x.size(), std::vector<double>(x[0].size()));
    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < x[0].size(); j++)
        {
            result[i][j] = x[i][j]+scalar;
        }
    }
    return result;
}

doubleVMat scalardivide(doubleVMat x, double scalar)
{
    doubleVMat result(x.size(), std::vector<double>(x[0].size()));
    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < x[0].size(); j++)
        {
            result[i][j] = x[i][j]/scalar;
        }
    }
    return result;
}

doubleVMat matsum(doubleVMat x, doubleVMat y)
{
    doubleVMat result(x.size(), std::vector<double>(x[0].size()));
    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < x[0].size(); j++)
        {
            result[i][j] = x[i][j]+y[i][j];
        }
    }
    return result;
}

doubleVMat matdot(doubleVMat x, doubleVMat y)
{
    doubleVMat result(x.size(), std::vector<double>(x[0].size()));
    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < x[0].size(); j++)
        {
            result[i][j] = x[i][j]*y[i][j];
        }
    }
    return result;
}

doubleVMat transpose(doubleVMat x)
{
    doubleVMat result(x[0].size(), std::vector<double>(x.size()));
    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < x[0].size(); j++)
        {
            result[j][i] = x[i][j];
        }
    }
    return result;
}

doubleVMat matmul(doubleVMat x, doubleVMat y)
{
    if (x[0].size() == y.size())
    {
        doubleVMat result(x.size(), std::vector<double>(y[0].size()));
        doubleVMat y_tranpose = transpose(y);
        for (int i = 0; i < x.size(); i++)
        {
            for (int j = 0; j < y[0].size(); j++)
            {
                double accum = 0;
                for (int k = 0; k < y_tranpose[0].size(); k++)
                {
                    accum += x[i][k]*y_tranpose[j][k];
                }
                result[i][j] = accum;
            }
        }
        return result;
    }
    else 
    {
        std::cout << "Matmul error: Shapes conflict.\n";
        exit(1);
    }
}

double matsummation(std::vector<doubleVMat> x)
{
    double accum = 0;
    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < x[i].size(); j++)
        {
            for (int k = 0; k < x[i][0].size(); k++)
            {
                accum += x[i][j][k];
            }
        }
    }
    return accum;
}

doubleVMat mean_squared_error_prime(doubleVMat estimated_y, doubleVMat y)
{
    return scalardivide(scalardot(matsum(y, scalardot(estimated_y, -1)), -2), estimated_y.size());
}

double matmean(doubleVMat x)
{
    double accum = 0;
    double size = 0;
    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < x[0].size(); j++)
        {
            accum += x[i][j];
            size += 1;
        }
    }
    return accum/size;
}

doubleVMat scalarpower(doubleVMat x, double y)
{
    doubleVMat result(x.size(), std::vector<double>(x[0].size()));
    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < x[0].size(); j++)
        {
            result[i][j] = pow(x[i][j], y);
        }
    }
    return result;
}

double mean_squared_error(doubleVMat estimated_y, doubleVMat y)
{
    return matmean(scalarpower(matsum(estimated_y, scalardot(y, -1)), 2));
}

doubleVMat sigmoid(doubleVMat x)
{
    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < x[0].size(); j++)
        {
            x[i][j] = 1/(1+(pow(exp(1.0), x[i][j])));
        }
    }
    return x;
}

doubleVMat sigmoid_prime(doubleVMat x)
{
    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < x[0].size(); j++)
        {
            x[i][j] = x[i][j]*(1-x[i][j]);
        }
    }
    return x;
}

#endif