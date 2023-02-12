#include <vector>
#include <functional>
#include <iostream>
#include <fstream>
#include <string>

class DataGenerator
{
public:
  DataGenerator(std::string path, int block_size) : 
    ifile(path),
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
  int block_size;
};
