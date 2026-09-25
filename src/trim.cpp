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

void stdsimd::TrimRightOne(char* str)
{
  namespace stdx = std::experimental;
  using simd_t = stdx::native_simd< char >;
  constexpr size_t simd_size = simd_t::size();

  char space = ' ';
  char end_str = '\0';

  size_t end_num = 0;
  size_t tail_space_num = 0;
  for (size_t i = 0; !end_num; i += simd_size)
  {
    simd_t values;
    values.copy_from(str + i, stdx::element_aligned);

    stdx::simd_mask< char > mask_end = values == simd_t(end_str);
    stdx::simd_mask< char > mask_space = (values != simd_t(space) && values != simd_t(end_str));
    if (stdx::any_of(mask_end))
    {
      end_num = i + stdx::find_first_set(mask_end);
    }
    if (stdx::any_of(mask_space))
    {
      size_t div = i + stdx::find_last_set(mask_space);
      if (!end_num || (end_num && div < end_num))
      {
        tail_space_num = div + 1;
      }
    }
  }
  char* end = str + end_num;
  char* tail_space = str + tail_space_num;
  if (tail_space != end)
  {
    *tail_space = '\0';
  }
}

void easy::TrimRight(char* str)
{
  char space = ' ';
  char end_delim = '\0';
  size_t i = 0;
  while (str[i] != end_delim)
  {
    ++i;
  }
  --i;

  while (str[i] == space)
  {
    --i;
  }
  str[i + 1] = '\0';
}

