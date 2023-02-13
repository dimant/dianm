#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <map>
#include <vector>

std::map<char, int> alphabetize(std::string path);

std::vector<int> encode(std::vector<char> block, std::map<char, int> vocab);

std::vector<char> decode(std::vector<int> block, std::map<int, char> vocab);

std::map<int, char> reversemap(std::map<char, int> vocab);

template <typename T>
void split_data(std::vector<T>& input_data, 
                std::vector<T>& training_data, 
                std::vector<T>& target_data, 
                float split_ratio);

#endif