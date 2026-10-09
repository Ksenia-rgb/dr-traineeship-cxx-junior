#include "trim.hpp"

#include <iostream>
#include <bit>

#ifdef __SSE2__
#include <emmintrin.h>

void trim::sse2::TrimRight(char* str)
{
  constexpr size_t simd_size = sizeof(__m128i);

  const char delim_end   = '\0';
  const char delim_space = ' ';

  const __m128i simd_delim_end = _mm_set1_epi8(delim_end);
  const __m128i simd_delim_space = _mm_set1_epi8(delim_space);

  size_t num_end = 0;

  for (size_t i = 0; !num_end; i += simd_size)
  {
    __m128i simd_values = _mm_loadu_si128(reinterpret_cast< const __m128i* >(str + i));

    __m128i cmp_end = _mm_cmpeq_epi8(simd_values, simd_delim_end);
    int mask_end = _mm_movemask_epi8(cmp_end);
    if (mask_end != 0)
    {
      num_end = i + __builtin_ctz(mask_end);
    }
  }

  char* temp = str + num_end;
  char* replace_for = nullptr;

  while (!replace_for && static_cast< size_t >(temp - str) >= simd_size)
  {
    __m128i simd_values = _mm_loadu_si128(reinterpret_cast< const __m128i* >(temp - simd_size));

    __m128i cmp_space = _mm_cmpeq_epi8(simd_values, simd_delim_space);
    int mask_space = _mm_movemask_epi8(cmp_space) ^ 0xFFFF; // need to invert only 16 low bits, because _mm_movemask_epi8 sets 0 for 16 high bits always
    if (mask_space != 0)
    {
      int last = sizeof(int) * 8 - 1 - __builtin_clz(mask_space);
      replace_for = temp - simd_size + last + 1;
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

#endif
