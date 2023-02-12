#include <iostream>

#include "DataGenerator.h"

int main()
{
    DataGenerator generator("data/input.txt", 8);

    std::cout << "Hello, CMake!" << std::endl;
    return 0;
}