#include "preprocessing.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

std::vector<std::pair<std::vector<int>, std::vector<int>>> 
blockify_vector(const std::vector<int>& input_vector, int block_size)
{
    int input_vector_size = input_vector.size();
    int num_blocks = (input_vector_size + block_size - 1) / block_size;
    
    std::vector<std::pair<std::vector<int>, std::vector<int>>> blocks;
    blocks.resize(num_blocks);
    
    for (int i = 0; i < num_blocks; i++)
    {
        int start_index = i * block_size;
        int block1_size = std::min(block_size, input_vector_size - start_index);
        int block2_size = std::min(block_size, input_vector_size - start_index - 1);
        
        blocks[i].first.resize(block_size, 0);
        blocks[i].second.resize(block_size, 0);
        
        std::copy(input_vector.begin() + start_index, 
                  input_vector.begin() + start_index + block1_size, 
                  blocks[i].first.begin());
        
        std::copy(input_vector.begin() + start_index + 1, 
                  input_vector.begin() + start_index + block2_size, 
                  blocks[i].second.begin());
    }
    
    return blocks;
}

template <typename T>
void split_data(std::vector<T>& input_data, 
                std::vector<T>& training_data, 
                std::vector<T>& target_data, 
                float split_ratio)
{
    int input_data_size = input_data.size();
    int training_data_size = std::ceil(input_data_size * split_ratio);
    
    training_data.resize(training_data_size);
    target_data.resize(input_data_size - training_data_size);
    
    std::vector<int> indices(input_data_size);
    std::iota(indices.begin(), indices.end(), 0);
    std::mt19937 rng(std::random_device{}());
    std::shuffle(indices.begin(), indices.end(), rng);
    
    for (int i = 0; i < training_data_size; ++i)
    {
        training_data[i] = input_data[indices[i]];
    }
    
    for (int i = training_data_size; i < input_data_size; ++i)
    {
        target_data[i - training_data_size] = input_data[indices[i]];
    }
}

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
    int index = 0;
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