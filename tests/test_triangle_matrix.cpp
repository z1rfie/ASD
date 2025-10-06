#include <windows.h>
#include <iostream>
#include "triangle_matrix.h"
#include <gtest/gtest.h>

#define EPSILON 0.000001

TEST(TestTriangleMatrixLib, default_constructor) {
    TriangleMatrix<int> mat;
    EXPECT_EQ(mat.get_n(), 0);
    EXPECT_TRUE(mat.is_empty());
}

TEST(TriangleMatrixTest, size_constructor) {
    TriangleMatrix<int> mat(3);
    EXPECT_EQ(mat.get_n(), 3);
    EXPECT_TRUE(mat.is_empty());
}
