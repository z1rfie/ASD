#include <windows.h>
#include <iostream>
#include "dsu.h"
#include <gtest/gtest.h>

TEST(TestDsuLib, init_constructor) {
	DSU dsu(10);
	EXPECT_EQ(dsu.size(), 10);

	for (size_t i = 0; i < dsu.size(); i++) {
		EXPECT_EQ(dsu.parent()[i], i);
	}
}

TEST(TestDsuLib, copy_constructor) {
	DSU dsu1(10);
	DSU dsu2(dsu1);
	EXPECT_EQ(dsu1.size(), 10);
	EXPECT_EQ(dsu2.size(), 10);

	for (size_t i = 0; i < dsu1.size(); i++) {
		EXPECT_EQ(dsu1.parent()[i], dsu2.parent()[i]);
	}
}

TEST(TestDsuLib, func_union_first_case) {
	DSU dsu(10);

	EXPECT_THROW(dsu.func_union(11, 4), std::out_of_range);
}

TEST(TestDsuLib, func_union_second_case) {
	DSU dsu(3);

	dsu.func_union(1, 1);

	for (size_t i = 0; i < dsu.size(); i++) {
		EXPECT_EQ(dsu.find(i), i);
	}
}

TEST(TestDsuLib, func_union_third_case) {
	DSU dsu(10);

	dsu.func_union(0, 1);
	dsu.func_union(1, 2);
	dsu.func_union(3, 4);
	dsu.func_union(2, 4);

	dsu.func_union(5, 6);

	dsu.func_union(6, 3);

	EXPECT_EQ(dsu.find(6), 0); 
	EXPECT_EQ(dsu.find(5), 0);
}


TEST(TestDsuLib, func_union_forth_case) {
	DSU dsu(6);

	dsu.func_union(0, 1);
	dsu.func_union(2, 3);
	dsu.func_union(4, 5);
	dsu.func_union(2, 4);

	dsu.func_union(1, 2);

	for (size_t i = 0; i < dsu.size(); i++) {
		EXPECT_EQ(dsu.find(i), 2);
	}
}

TEST(TestDsuLib, func_union_fifth_case) {
	DSU dsu(5);

	dsu.func_union(0, 1);
	dsu.func_union(1, 2);
	dsu.func_union(3, 4);
	dsu.func_union(2, 4);

	for (size_t i = 0; i < dsu.size(); i++) {
		EXPECT_EQ(dsu.find(i), 0);
	}
}

TEST(TestDsuLib, find_error) {
	DSU dsu(5);

	EXPECT_THROW(dsu.find(11), std::out_of_range);
}

TEST(TestDsuLib, find) {
	DSU dsu(5);

	dsu.func_union(0, 1);
	dsu.func_union(1, 2);

	EXPECT_EQ(dsu.find(2), 0);
}

TEST(TestDsuLib, find_rec_first_case) {
	DSU dsu(5);

	dsu.func_union(0, 0);

	EXPECT_EQ(dsu.find_rec(0), 0);
}

TEST(TestDsuLib, find_rec_second_case) {
	DSU dsu(5);

	dsu.parent()[1] = 0;
	dsu.parent()[2] = 1;
	dsu.parent()[3] = 2;
	dsu.parent()[4] = 3;

	EXPECT_EQ(dsu.parent()[4], 3);
	EXPECT_EQ(dsu.find_rec(4), 0);
	EXPECT_EQ(dsu.parent()[4], 0);
}

TEST(TestDsuLib, test) {
	DSU dsu(6);

	dsu.func_union(0, 1);
	
	dsu.func_union(2, 3);

	dsu.func_union(4, 5);

	dsu.func_union(3, 5);
	dsu.func_union(1, 5);

	EXPECT_EQ(dsu.rank()[2], 2);
}