#include <string>
#include <iostream>
#include <fstream>

#include "trim.hpp"

int main(int argc, char* argv[])
{
  std::string str;
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

  using trim_t = void(*)(char*);
  trim_t trim_platform_func = nullptr;

  #ifdef __SSE2__
  #ifndef __AVX2__
  trim_platform_func = trim::sse2::TrimRight;
  #endif
  #endif

  #ifdef __AVX2__
  trim_platform_func = trim::avx2::TrimRight;
  #endif

  #ifdef __ARM_NEON
  trim_platform_func = trim::neon::TrimRight;
  #endif

  trim::scalar::TrimRight(str1.data());
  trim::stdsimd::TrimRight(str2.data());
  trim_platform_func(str3.data());
}
