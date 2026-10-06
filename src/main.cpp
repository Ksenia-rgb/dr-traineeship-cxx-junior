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
  char str1[] = " a  aa       ";
  char str2[] = "f   gd                              ";
  char str3[] = "h   hh                   ";
  //std::string str1 = str;
  //std::string str2 = str;
  //std::string str3 = str;

  using trim_t = void(*)(char*);
  trim_t trim_platform_func = nullptr;

  #ifdef __SSE2__
  trim_platform_func = trim::sse2::TrimRight;
  #endif

  #ifdef __AVX2__
  trim_platform_func = trim::avx2::TrimRight;
  #endif

  #ifdef __ARM_NEON
  trim_platform_func = trim::neon::TrimRight;
  #endif

  #if defined(__riscv_v_intrinsic) && defined(__riscv_vector)
  trim_platform_func = trim::riscv::TrimRight;
  #endif

  std::cout << str1 << str2 << str3 << "end\n";

  trim::scalar::TrimRight(str1);
  trim::stdsimd::TrimRight(str2);
  trim_platform_func(str3);

  std::cout << str1 << str2 << str3 << "end\n";
}
