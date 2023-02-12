#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <map>

std::map<char, int> alphabetize(std::string path);

std::vector<int> encode(std::vector<char> block, std::map<char, int> vocab);

std::vector<char> decode(std::vector<int> block, std::map<int, char> vocab);

std::map<int, char> reversemap(std::map<char, int> vocab);

#endif