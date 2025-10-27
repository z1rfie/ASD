#include <windows.h>
#include <iostream>
#include "algorithms.h"
#include <gtest/gtest.h>

TEST(TestAlgorithmsLib, test_check_breckets) {
	std::string str1 = "()()";
	std::string str2 = "[(()())({})";
	std::string str3 = "[(()())({})]";
	
	EXPECT_EQ(check_breckets(str1), true);
	EXPECT_EQ(check_breckets(str2), false);
	EXPECT_EQ(check_breckets(str3), true);
}

TEST(TestAlgorithmsLib, test_read_expression) {
	std::string str1 = "()()";
	std::string str2 = "[(()())({})";
	std::string str3 = "[(()())({})]";

	EXPECT_THROW(read_expression(str2), std::invalid_argument);
}