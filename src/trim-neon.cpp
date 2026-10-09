#include "trim.hpp"

#include <iostream>

#ifdef __ARM_NEON
#include <arm_neon.h>

namespace
{
  int first_set_u8(uint8x16_t cmp)
  {
    uint8x8_t tmp = vshrn_n_u16(vreinterpretq_u16_u8(cmp), 4);
    uint64_t m = vget_lane_u64(vreinterpret_u64_u8(tmp), 0);
    if (m == 0)
    {
      return -1;
    }

    unsigned p = __builtin_ctzll(m);
    unsigned i = p / 8;

    if (m & (0x0FULL << (8 * i)))
    {
      return static_cast< int >(2 * i);
    }
    else
    {
      return static_cast< int >(2 * i + 1);
    }
  }

  int last_set_u8(uint8x16_t cmp)
  {
    uint8x8_t tmp = vshrn_n_u16(vreinterpretq_u16_u8(cmp), 4);
    uint64_t  m   = vget_lane_u64(vreinterpret_u64_u8(tmp), 0);
    if (m == 0)
    {
      return -1;
    }

    unsigned p = 63u - static_cast< unsigned >(__builtin_clzll(m));
    unsigned i = p / 8;

    if (m & (0xF0ULL << (8 * i)))
    {
      return static_cast< int >(2 * i + 1);
    }
    else
    {
      return static_cast< int >(2 * i);
    }
  }
}

void trim::neon::TrimRight(char* str)
{
  constexpr size_t simd_size = sizeof(uint8x16_t);

  const char delim_end = '\0';
  const char delim_space = ' ';

  const uint8x16_t simd_delim_end = vdupq_n_u8(delim_end);
  const uint8x16_t simd_delim_space = vdupq_n_u8(delim_space);

  size_t num_end = 0;

  for (size_t i = 0; !num_end; i += simd_size)
  {
    uint8x16_t simd_values = vld1q_u8(reinterpret_cast< const uint8_t* >(str + i));
    
    uint8x16_t mask_end = vceqq_u8(simd_values, simd_delim_end);
    int first = first_set_u8(mask_end);
    if (first >= 0)
    {
      num_end = i + first;
    }
  }

  char* temp = str + num_end;
  char* replace_for = nullptr;

  while (!replace_for && static_cast< size_t >(temp - str) >= simd_size)
  {
    uint8x16_t simd_values = vld1q_u8(reinterpret_cast< const uint8_t* >(temp - simd_size));

    uint8x16_t mask_space = vmvnq_u8(vceqq_u8(simd_values, simd_delim_space));
    int last = last_set_u8(mask_space);
    if (last >= 0)
    {
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
