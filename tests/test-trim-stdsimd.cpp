#include <boost/test/unit_test.hpp>
#include "trim.hpp"

BOOST_AUTO_TEST_CASE(test_stdsimd_empty_str)
{
  char str[] = "";
  trim::stdsimd::TrimRight(str);
  BOOST_TEST(str == "");
}

BOOST_AUTO_TEST_CASE(test_stdsimd_str_without_spaces)
{
  char str[] = "aaa";
  trim::stdsimd::TrimRight(str);
  BOOST_TEST(str == "aaa");
}

BOOST_AUTO_TEST_CASE(test_stdsimd_str_only_spaces)
{
  char str[] = "  ";
  trim::stdsimd::TrimRight(str);
  BOOST_TEST(str == "");
}

BOOST_AUTO_TEST_CASE(test_stdsimd_str_bigger_than_one_simd_size)
{
  char str[] = "a                                      ";
  trim::stdsimd::TrimRight(str);
  BOOST_TEST(str == "a");
}

BOOST_AUTO_TEST_CASE(test_stdsimd_str_bigger_than_one_simd_size_only_spaces)
{
  char str[] = "                                           ";
  trim::stdsimd::TrimRight(str);
  BOOST_TEST(str == "");
}

BOOST_AUTO_TEST_CASE(test_stdsimd_str_with_spaces_middle_simd_size)
{
  char str[] = "      aaaaaaaaaaaaa                                      ";
  trim::stdsimd::TrimRight(str);
  BOOST_TEST(str == "      aaaaaaaaaaaaa");
}
