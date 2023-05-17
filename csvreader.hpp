#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "matrix.hpp"
#include "dictionary.hpp"

std::vector<std::vector<std::string>> get_all_rows(std::fstream &f_stream)
{
    std::string line_buffer;
    int line_count = 0;
    std::vector<std::vector<std::string>> result;
    if (f_stream.good())
    {
        std::vector<std::string> line;
        f_stream >> line_buffer;
        std::stringstream constructor;
        for (int i = 0; i <= line_buffer.length(); i++)
        {
            if (line_buffer[i] != ',' && i < line_buffer.length())
            {
                constructor << line_buffer[i];
            }
            else
            {
                line.push_back(constructor.str());
                line_count++;
                constructor.str(std::string());
            }
        }
        result.push_back(line);
    }
    while (f_stream.good())
    {
        f_stream >> line_buffer;
        std::stringstream constructor;
        std::vector<std::string> line;
        for (int i = 0; i <= line_buffer.length() && line.size() <= line_count; i++)
        {
            if (line_buffer[i] != ',' && i < line_buffer.length())
            {
                constructor << line_buffer[i];
            }
            else
            {
                line.push_back(constructor.str());
                constructor.str(std::string());
            }
        }
        result.push_back(line);
    }
    return result;
}

std::vector<std::string> get_column(std::vector<std::vector<std::string>> m, int r)
{ 
    std::vector<std::string> row;
    for (int j = 0; j < m.size(); j++)
    {
        row.push_back(m[j][r]);
    }
    return row;
}

Matrix encode_str_matrix(std::vector<std::vector<std::string>> str_matrix)
{
    Matrix result(str_matrix.size(), str_matrix[0].size());
    Dictionary<long double> encoder;
    for (int i = 0; i < str_matrix[0].size(); i++)
    {
        int encode = 0;
        try
        {
            std::stold(str_matrix[0][i]);
        }
        catch (const std::exception &e)
        {
            encoder.clear();
            std::vector<std::string> col = get_column(str_matrix, i);
            encoder = uniques_dict(col);
            encode = 1;
        }

        for (int j = 0; j < str_matrix.size(); j++)
        {
            if (!encode)
            {
                result.set(j, i, std::stold(str_matrix[j][i]));
            }
            else
            {
                result.set(j, i, encoder.get(str_matrix[j][i]));
            }
        }
    }
    return result;
}

Matrix matrix_from_csv(std::string fp)
{
    std::fstream csv_file(fp);
    std::vector<std::vector<std::string>> str_data = get_all_rows(csv_file);
    csv_file.close();
    return encode_str_matrix(str_data);
}