#include <vector>
#include <functional>
#include <iostream>
#include <fstream>
#include <string>

class DataGenerator
{
public:
    DataGenerator(const std::string &path, const int block_size) : ifile(path),
                                                                   block_size(block_size)
    {
    }

    ~DataGenerator()
    {
        ifile.close();
    }

    std::vector<char> operator()();

private:
    std::ifstream ifile;
    const int block_size;
};
