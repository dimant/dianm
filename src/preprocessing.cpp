#include "preprocessing.h"

#include <fstream>
#include <iostream>

std::map<char, int> getAlphabet(std::string path)
{
    auto vocab = std::map<char, int>();
    std::ifstream ifile(path);
    int index = 1;
    char c;

    if (!ifile) {
        std::cerr << "Could not open file" << std::endl;
        throw;
    }

    while(ifile.get(c))
    {
        if (vocab.find(c) == vocab.end())
        {
            vocab[c] = index++;
        }
    }

    ifile.close();

    return vocab;
}