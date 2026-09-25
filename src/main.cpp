#include <string>
#include <iostream>
#include <fstream>
#include <valgrind/callgrind.h>

#include "trim.hpp"

int main(int argc, char* argv[])
{
  std::string str{"fgd____________"};
  if (argc == 2)
  {
    std::ifstream fin(argv[1], std::ios::binary | std::ios::ate);
    if (!fin.is_open())
    {
      std::cerr << "Incorrect file\n";
      return 1;
    }
    std::streamsize size = fin.tellg();
    fin.seekg(0);
    str.resize(size);
    fin.read(str.data(), size);
  }
  std::string str1 = str;
  std::string str2 = str;
  std::string str3 = str;

  for (size_t i = 0; i < 10; i++)
  {
    stdsimd::TrimRight(str2.data());
    easy::TrimRight(str1.data());

    str1 = str;
    str2 = str;
    str3 = str;
  }
}
