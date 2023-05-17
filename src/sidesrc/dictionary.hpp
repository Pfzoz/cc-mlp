#ifndef DICTIONARY
#define DICTIONARY

#include <vector>

template <typename T>
struct Dictionary
{
    std::vector<std::string> keys;
    std::vector<T> values;
    Dictionary(){};
    void set(std::string key, T value)
    {
        int contains = 0;
        for (int i = 0; i < keys.size(); i++)
        {
            if (key == keys[i])
                contains = 1;
        }
        if (!contains)
        {
            keys.push_back(key);
            values.push_back(value);
        }
    }
    T get(std::string key)
    {
        T result;
        for (int i = 0; i < keys.size(); i++)
        {
            if (keys[i] == key)
                result = values[i];
        }
        return result;
    }
    void clear()
    {
        keys.clear();
        values.clear();
        std::vector<std::string> empty;
        std::vector<T> empty_values;
        keys.swap(empty);
        values.swap(empty_values);
    }
};

std::vector<std::string> find_all_unique(std::vector<std::string> v)
{
    std::vector<std::string> result;
    for (int i = 0; i < v.size(); i++)
    {
        int contains = 0;
        for (int j = 0; j < result.size(); j++)
        {
            if (v[i] == result[j]) contains = 1;
        }
        if (!contains)
        {
            result.push_back(v[i]);
        }
    }
    return result;
}

int check_uniques(std::vector<std::string> str_v)
{
    int is_unique = 1;
    for (int i = 0; i < str_v.size(); i++)
    {
        for (int j = i+1; j < str_v.size(); j++)
        {
            if (str_v[i] == str_v[j]) is_unique = 0;
        }
    }
    return is_unique;
}

Dictionary<long double> uniques_dict(std::vector<std::string> unique_v)
{
    Dictionary<long double> dict;
    if (!check_uniques(unique_v))
    {
        unique_v = find_all_unique(unique_v);   
    }
    for (int i = 0; i < unique_v.size(); i++)
    {
        dict.set(unique_v[i], i);
    }
    return dict;
}

#endif