#include <boost/test/unit_test.hpp>
#include "trim.hpp"

BOOST_AUTO_TEST_CASE(test_scalar_empty_str)
{
  char str[] = "";
  trim::scalar::TrimRight(str);
  BOOST_TEST(str == "");
}

BOOST_AUTO_TEST_CASE(test_scalar_str_without_spaces)
{
  char str[] = "aaa";
  trim::scalar::TrimRight(str);
  BOOST_TEST(str == "aaa");
}

BOOST_AUTO_TEST_CASE(test_scalar_str_only_spaces)
{
  char str[] = "  ";
  trim::scalar::TrimRight(str);
  BOOST_TEST(str == "");
}

BOOST_AUTO_TEST_CASE(test_scalar_big_str)
{
  char str[] = "a                ";
  trim::scalar::TrimRight(str);
  BOOST_TEST(str == "a");
}
