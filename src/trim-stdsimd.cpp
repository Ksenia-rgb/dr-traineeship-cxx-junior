#include "trim.hpp"

#include <iostream>
#include <experimental/simd>

void trim::stdsimd::TrimRight(char* str)
{
  std::cout << "STDSIMD\n";

  namespace stdx = std::experimental;
  using simd_t = stdx::native_simd< char >;
  constexpr size_t simd_size = simd_t::size();

  const char delim_end = '\0';
  const char delim_space = ' ';

  const simd_t simd_delim_end{delim_end};
  const simd_t simd_delim_space{delim_space};

  size_t num_end = 0;

  for (size_t i = 0; !num_end; i += simd_size)
  {
    simd_t simd_values;
    simd_values.copy_from(str + i, stdx::element_aligned);

    stdx::simd_mask< char > mask_end = (simd_values == simd_delim_end);
    if (stdx::any_of(mask_end))
    {
      num_end = i + stdx::find_first_set(mask_end);
    }
  }

  char* temp = str + num_end;
  char* replace_for = nullptr;

  while (!replace_for && static_cast< size_t >(temp - str) >= simd_size)
  {
    simd_t simd_values;
    simd_values.copy_from(temp - simd_size, stdx::element_aligned);

    stdx::simd_mask< char > mask_space = (simd_values != simd_delim_space);
    if (stdx::any_of(mask_space))
    {
      replace_for = temp - simd_size + stdx::find_last_set(mask_space) + 1;
    }

    temp -= simd_size;
  }
  while (!replace_for && temp != str)
  {
    --temp;
    if (*temp != delim_space)
    {
      replace_for = temp + 1;
    }
  }
  if (!replace_for)
  {
    replace_for = str;
  }
  *replace_for = delim_end;
}

void trim::stdsimd::TrimRightOnePass(char* str)
{
  std::cout << "STDSIMD ONEPASS\n";

  namespace stdx = std::experimental;
  using simd_t = stdx::native_simd< char >;
  constexpr size_t simd_size = simd_t::size();

  const char delim_end = '\0';
  const char delim_space = ' ';

  const simd_t simd_delim_end{delim_end};
  const simd_t simd_delim_space{delim_space};

  size_t num_end = 0;
  size_t num_replace_for = 0;

  for (size_t i = 0; !num_end; i += simd_size)
  {
    simd_t simd_values;
    simd_values.copy_from(str + i, stdx::element_aligned);

    stdx::simd_mask< char > mask_end = (simd_values == simd_delim_end);
    if (stdx::any_of(mask_end))
    {
      num_end = i + stdx::find_first_set(mask_end);

      simd_t simd_tail;
      simd_tail.copy_from(str + num_end - simd_size, stdx::element_aligned);

      stdx::simd_mask< char > mask_space = (simd_tail != simd_delim_space);
      if (stdx::any_of(mask_space))
      {
        num_replace_for = num_end - simd_size + stdx::find_last_set(mask_space) + 1;
      }
    }
    else
    {
      stdx::simd_mask< char > mask_space = (simd_values != simd_delim_space);
      if (stdx::any_of(mask_space))
      {
        num_replace_for = i + stdx::find_last_set(mask_space) + 1;
      }
    }
  }

  char* replace_for = str + num_replace_for;
  *replace_for = delim_end;
}
