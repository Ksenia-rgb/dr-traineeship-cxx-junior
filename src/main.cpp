#include <iostream>

#include "trim.hpp"

namespace
{
  void trimRightGeneral(char* str);

  void trimRightGeneral(char* str)
  {
    char end_delim = '\0';
    size_t i = 0;
    while (str[i] != end_delim)
    {
      ++i;
    }
    --i;

    while (std::isspace(static_cast< int >(str[i])) || static_cast< int >(str[i]) == '_')
    {
      --i;
    }
    str[i + 1] = '\0';
  }
}


int main()
{
  std::string str{"dfj____________nsjdf__________________________________________________"};
  char* char_str = str.data();
  trimRightGeneral(char_str);
  std::cout << char_str << '\n';
}
