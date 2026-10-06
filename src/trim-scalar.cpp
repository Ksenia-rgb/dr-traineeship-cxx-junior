#include "trim.hpp"

#include <iostream>
#include <cstddef>

void trim::scalar::TrimRight(char* str)
{
  std::cout << "SCALAR\n";

  char delim_end = '\0';
  char delim_space = ' ';

  size_t i = 0;
  while (str[i] != delim_end)
  {
    ++i;
  }
  --i;

  while (str[i] == delim_space)
  {
    --i;
  }
  str[i + 1] = delim_end;
}
