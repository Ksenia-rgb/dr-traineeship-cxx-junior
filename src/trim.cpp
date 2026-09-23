#include "trim.hpp"

#include <experimental/simd>
#include <immintrin.h>

#include <iostream>

void stdsimd::TrimRight(char* str)
{
  namespace stdx = std::experimental;
  using simd_t = stdx::native_simd< char >;
  constexpr size_t simd_size = simd_t::size();

  char* end = nullptr;
  for (size_t i = 0; !end; i += simd_size)
  {
    simd_t values;
    values.copy_from(str + i, stdx::element_aligned);

    stdx::simd_mask< char > mask = values == simd_t('\0');
    if (stdx::any_of(mask))
    {
      end = str + i + stdx::find_first_set(mask);
    }
  }

  char* temp = end - 1;
  char* replace_for = nullptr;
  while (!replace_for && static_cast< size_t >(temp - str) >= simd_size)
  {
    simd_t values;
    values.copy_from(temp - simd_size, stdx::element_aligned);

    stdx::simd_mask< char > mask = values != simd_t('_');
    if (stdx::any_of(mask))
    {
      replace_for = temp - simd_size + stdx::find_last_set(mask) + 1;
    }

    temp -= simd_size;
  }
  if (!replace_for)
  {
    /*stdx::simd_mask mask = stdx::where(stdx::native_simd< size_t >(
      [str](char* j)
      {
        return j > str ? 1u : 0u;
      }
    ) != 0, stdx::simd_mask< char >(true));
    }*/
    simd_t values;
    values.copy_from(str, stdx::element_aligned);
    stdx::simd_mask< char > mask = values != simd_t('_');
    if (stdx::all_of(mask))
    {
      replace_for = str + simd_size;
    }
    else if (stdx::any_of(mask))
    {
      replace_for = str + stdx::find_last_set(mask) + 1;
    }
    else
    {
      replace_for = str;
    }
  }
  *replace_for = '\0';
}

/*void intrinsimd::TrimRight(char* str)
{
}*/

void easy::TrimRight(char* str)
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

