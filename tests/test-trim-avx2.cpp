#include <boost/test/unit_test.hpp>
#include <trim.hpp>

#ifdef __AVX2__

BOOST_AUTO_TEST_CASE(test_avx2_empty_str)
{
  char str[] = "";
  trim::avx2::TrimRight(str);
  BOOST_TEST(str == "");
}

BOOST_AUTO_TEST_CASE(test_avx2_str_without_spaces)
{
  char str[] = "aaa";
  trim::avx2::TrimRight(str);
  BOOST_TEST(str == "aaa");
}

BOOST_AUTO_TEST_CASE(test_avx2_str_only_spaces)
{
  char str[] = "  ";
  trim::avx2::TrimRight(str);
  BOOST_TEST(str == "");
}

BOOST_AUTO_TEST_CASE(test_avx2_str_bigger_than_one_simd_size)
{
  char str[] = "a                                      ";
  trim::avx2::TrimRight(str);
  BOOST_TEST(str == "a");
}

BOOST_AUTO_TEST_CASE(test_avx2_str_bigger_than_one_simd_size_only_spaces)
{
  char str[] = "                                           ";
  trim::avx2::TrimRight(str);
  BOOST_TEST(str == "");
}

BOOST_AUTO_TEST_CASE(test_avx2_str_with_spaces_middle_simd_size)
{
  char str[] = "      aaaaaaaaaaaaa                                      ";
  trim::avx2::TrimRight(str);
  BOOST_TEST(str == "      aaaaaaaaaaaaa");
}

#endif
