#include "preprocessing.h"

#include <fstream>
#include <iostream>
#include <vector>

std::vector<int> encode(const std::vector<char> &block, std::map<char, int> vocab)
{
    auto encoded = std::vector<int>();
    for (auto c : block)
    {
        encoded.push_back(vocab[c]);
    }

    return encoded;
}

std::vector<char> decode(const std::vector<int> &block, std::map<int, char> vocab)
{
    auto decoded = std::vector<char>();
    for (auto i : block)
    {
        decoded.push_back(vocab[i]);
    }

    return decoded;
}

std::map<int, char> reversemap(const std::map<char, int> &vocab)
{
    auto reverse = std::map<int, char>();
    for (auto pair : vocab)
    {
        reverse[pair.second] = pair.first;
    }

    return reverse;
}

std::map<char, int> alphabetize(std::string path)
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