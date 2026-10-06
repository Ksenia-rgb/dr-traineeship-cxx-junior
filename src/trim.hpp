#ifndef TRIM_HPP
#define TRIM_HPP

namespace trim
{
  namespace stdsimd
  {
    void TrimRight(char* str);
    void TrimRightOnePass(char* str);
  }
  namespace sse2
  {
    void TrimRight(char* str);
  }
  namespace avx2
  {
    void TrimRight(char* str);
  }
  namespace neon
  {
    void TrimRight(char* str);
  }
  namespace riscv
  {
    void TrimRight(char* str);
  }
  namespace scalar
  {
    void TrimRight(char* str);
  }
}

#endif
