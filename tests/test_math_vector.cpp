#include <windows.h>
#include <iostream>
#include "matrix.h"
#include <gtest/gtest.h>

#define EPSILON 0.000001

TEST(MatrixAdditionTest, BasicAddition) {
    Matrix<int> A(2, 2);
    Matrix<int> B(2, 2);

    A[0][0] = 1; A[0][1] = 2;
    A[1][0] = 3; A[1][1] = 4;

    B[0][0] = 5; B[0][1] = 6;
    B[1][0] = 7; B[1][1] = 8;

    Matrix<int> C = A + B;

    EXPECT_EQ(C[0][0], 6);
    EXPECT_EQ(C[0][1], 8);
    EXPECT_EQ(C[1][0], 10);
    EXPECT_EQ(C[1][1], 12);
}