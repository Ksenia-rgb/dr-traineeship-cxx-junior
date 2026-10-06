#include "trim.hpp"

#include <iostream>

#if defined(__riscv_v_intrinsic) && defined(__riscv_vector)
#include <riscv_vector.h>

void trim::riscv::TrimRight(char* str)
{
  std::cout << "RISCV\n";
}

#endif
