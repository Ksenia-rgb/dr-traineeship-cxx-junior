#include <iostream>

#include "trim.hpp"

int main()
{
  std::string str{"dfj____________________"};
  //char* char_str1 = str.data();
  char* char_str2 = str.data();

  //easy::TrimRight(char_str1);
  //std::cout << char_str1 << '\n';

  stdsimd::TrimRight(char_str2);
  std::cout << char_str2 << '\n';
}
