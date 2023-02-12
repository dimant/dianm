#include <iostream>

#include "DataGenerator.h"
#include "preprocessing.h"

int main()
{
    int block_size = 8;
    auto vocab = alphabetize("./data/input.txt");

    DataGenerator generator("./data/input.txt", block_size);

    while (true)
    {
        auto data = generator();
        if (data[block_size - 1] == '\0')
        {
            break;
        }

        std::string s = std::string(data.begin(), data.end());

        std::cout << s << std::endl;
    }

    return 0;
}