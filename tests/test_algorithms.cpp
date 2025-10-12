#include <windows.h>
#include <iostream>
#include "algorithms.h"
#include <gtest/gtest.h>

TEST(TestAlgorithmsLib, test_find_local_min) {
    Matrix<int> matr(3, 3);
    matr[0][0] = 7; matr[0][1] = 1; matr[0][2] = 3;
    matr[1][0] = 4; matr[1][1] = 5; matr[1][2] = 6;
    matr[2][0] = 2; matr[2][1] = 8; matr[2][2] = 9;

    EXPECT_EQ(find_local_min(matr, 1, 1), 1);
    EXPECT_EQ(find_local_min(matr, 1, 0), 2);
}

TEST(TestAlgorithmsLib, test_find_local_min_size_4) {
    Matrix<int> matr(4, 4);
    matr[0][0] = 11; matr[0][1] = 15; matr[0][2] = 10; matr[0][3] = 9;
    matr[1][0] = 6;  matr[1][1] = 16; matr[1][2] = 3;  matr[1][3] = 8;
    matr[2][0] = 7;  matr[2][1] = 4;  matr[2][2] = 2;  matr[2][3] = 13;
    matr[3][0] = 14; matr[3][1] = 12; matr[3][2] = 1;  matr[3][3] = 5;

    EXPECT_EQ(find_local_min(matr, 2, 0), 1);
}

TEST(TestAlgorithmsLib, test_find_local_min_different_n_and_m) {
    Matrix<int> matr(2, 3);
    matr[0][0] = 7; matr[0][1] = 1; matr[0][2] = 3;
    matr[1][0] = 4; matr[1][1] = 5; matr[1][2] = 6;

    EXPECT_THROW(find_local_min(matr, 1, 1), std::exception);
}

TEST(TestAlgorithmsLib, test_find_local_min_error_index) {
    Matrix<int> matr(3, 3);
    matr[0][0] = 7; matr[0][1] = 1; matr[0][2] = 3;
    matr[1][0] = 4; matr[1][1] = 5; matr[1][2] = 6;
    matr[2][0] = 2; matr[2][1] = 8; matr[2][2] = 9;

    EXPECT_THROW(find_local_min(matr, 3, 3), std::exception);
}