#include <vector>
#include <functional>
#include <iostream>
#include <fstream>
#include <string>

#include "DataGenerator.h"

std::vector<char> DataGenerator::operator()()
{
    std::vector<char> result;
    result.reserve(block_size);

    for (int i = 0; i < block_size; ++i)
    {
        if (ifile.eof())
        {
            result.push_back('\0');
        }
        else
        {
            char c;
            ifile.get(c);
            result.push_back(c);
        }
    }

    return result;
}