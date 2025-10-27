#include <gtest/gtest.h>
#include "triangle_matrix.h"

TEST(TestTriangleMatrix, default_constructor) {
    TriangleMatrix<int> mat;
    EXPECT_EQ(mat.get_n(), 0);
    EXPECT_EQ(mat.get_m(), 0);
}

TEST(TestTriangleMatrix, size_constructor) {
    TriangleMatrix<int> mat(3);
    EXPECT_EQ(mat.get_n(), 3);
    EXPECT_EQ(mat.get_m(), 3);
}

TEST(TestTriangleMatrix, index_operator) {
    TriangleMatrix<int> mat(2);
    mat[0][0] = 1;
    mat[0][1] = 2;
    mat[1][1] = 3;

    EXPECT_EQ(mat[0][0], 1);
    EXPECT_EQ(mat[0][1], 2);
    EXPECT_EQ(mat[1][1], 3);
}

TEST(TestTriangleMatrix, const_index_operator) {
    TriangleMatrix<int> mat(2);
    mat[0][0] = 5;
    const TriangleMatrix<int>& const_mat = mat;
    EXPECT_EQ(const_mat[0][0], 5);
}

TEST(TestTriangleMatrix, at) {
    TriangleMatrix<int> mat(2);
    mat.at(0, 0) = 5;
    EXPECT_EQ(mat.at(0, 0), 5);
}

TEST(TestTriangleMatrix, at_error) {
    TriangleMatrix<int> mat(2);
    EXPECT_THROW(mat.at(5, 5), std::out_of_range);
}

TEST(TestTriangleMatrix, addition) {
    TriangleMatrix<int> mat1(2);
    TriangleMatrix<int> mat2(2);

    mat1[0][0] = 1; mat1[0][1] = 2;
    mat1[1][1] = 3;

    mat2[0][0] = 4; mat2[0][1] = 5;
    mat2[1][1] = 6;

    TriangleMatrix<int> result = mat1 + mat2;
    EXPECT_EQ(result[0][0], 5);
    EXPECT_EQ(result[0][1], 7);
    EXPECT_EQ(result[1][1], 9);
}

TEST(TestTriangleMatrix, addition_assignment) {
    TriangleMatrix<int> mat1(2);
    TriangleMatrix<int> mat2(2);

    mat1[0][0] = 1; mat1[0][1] = 2;
    mat2[0][0] = 3; mat2[0][1] = 4;

    mat1 += mat2;
    EXPECT_EQ(mat1[0][0], 4);
    EXPECT_EQ(mat1[0][1], 6);
}

TEST(TestTriangleMatrix, addition_assignment_self) {
    TriangleMatrix<int> mat(2);
    mat[0][0] = 1;
    mat += mat;
    EXPECT_EQ(mat[0][0], 2);
}

TEST(TestTriangleMatrix, subtraction) {
    TriangleMatrix<int> mat1(2);
    TriangleMatrix<int> mat2(2);

    mat1[0][0] = 5; mat1[0][1] = 7;
    mat2[0][0] = 2; mat2[0][1] = 3;

    TriangleMatrix<int> result = mat1 - mat2;
    EXPECT_EQ(result[0][0], 3);
    EXPECT_EQ(result[0][1], 4);
}

TEST(TestTriangleMatrix, subtraction_negative_result) {
    TriangleMatrix<int> mat1(2);
    TriangleMatrix<int> mat2(2);

    mat1[0][0] = 1;
    mat2[0][0] = 3;

    TriangleMatrix<int> result = mat1 - mat2;
    EXPECT_EQ(result[0][0], -2);
}

TEST(TestTriangleMatrix, subtraction_assignment) {
    TriangleMatrix<int> mat1(2);
    TriangleMatrix<int> mat2(2);

    mat1[0][0] = 10;
    mat2[0][0] = 3;

    mat1 -= mat2;
    EXPECT_EQ(mat1[0][0], 7);
}

TEST(TestTriangleMatrix, subtraction_assignmentZero) {
    TriangleMatrix<int> mat(2);
    mat[0][0] = 5;
    mat -= mat;
    EXPECT_EQ(mat[0][0], 0);
}

TEST(TestTriangleMatrix, scalar_multiplication) {
    TriangleMatrix<int> mat(2);
    mat[0][0] = 2; mat[0][1] = 3;
    mat[1][1] = 4;

    TriangleMatrix<int> result = mat * 3;
    EXPECT_EQ(result[0][0], 6);
    EXPECT_EQ(result[0][1], 9);
    EXPECT_EQ(result[1][1], 12);
}

TEST(TestTriangleMatrix, scalar_multiplication_zero) {
    TriangleMatrix<int> mat(2);
    mat[0][0] = 5;
    TriangleMatrix<int> result = mat * 0;
    EXPECT_EQ(result[0][0], 0);
}

TEST(TestTriangleMatrix, scalar_multiplication_assignment) {
    TriangleMatrix<int> mat(2);
    mat[0][0] = 2;
    mat *= 4;
    EXPECT_EQ(mat[0][0], 8);
}

TEST(TestTriangleMatrix, acalar_multiplication_assignment_one) {
    TriangleMatrix<int> mat(2);
    mat[0][0] = 5;
    mat *= 1;
    EXPECT_EQ(mat[0][0], 5);
}

TEST(TriangleMatrix, matrix_multiplication) {
    TriangleMatrix<int> mat1(2);
    TriangleMatrix<int> mat2(2);

    mat1[0][0] = 1; mat1[0][1] = 2;
    mat1[1][1] = 3;

    mat2[0][0] = 4; mat2[0][1] = 5;
    mat2[1][1] = 6;

    TriangleMatrix<int> result = mat1 * mat2;
    EXPECT_EQ(result[0][0], 4);
    EXPECT_EQ(result[0][1], 17);
    EXPECT_EQ(result[1][1], 18);
}

TEST(TestTriangleMatrix, matrix_multiplication_identity) {
    TriangleMatrix<int> mat(2);
    TriangleMatrix<int> identity(2);

    mat[0][0] = 1; mat[0][1] = 2;
    mat[1][1] = 3;

    identity[0][0] = 1; identity[0][1] = 0;
    identity[1][1] = 1;

    TriangleMatrix<int> result = mat * identity;
    EXPECT_EQ(result[0][0], 1);
    EXPECT_EQ(result[0][1], 2);
    EXPECT_EQ(result[1][1], 3);
}

TEST(TestTriangleMatrix, vector_multiplication) {
    TriangleMatrix<int> mat(2);
    MathVector<int> vec(2);

    mat[0][0] = 1; mat[0][1] = 2;
    mat[1][1] = 3;

    vec[0] = 4; vec[1] = 5;

    MathVector<int> result = mat * vec;
    EXPECT_EQ(result[0], 14);
    EXPECT_EQ(result[1], 15);
}

TEST(TriangleMatrix, vector_multiplication_wrong_size) {
    TriangleMatrix<int> mat(2);
    MathVector<int> vec(3);
    EXPECT_THROW(mat * vec, std::invalid_argument);
}

TEST(TestTriangleMatrix, equality_operator) {
    TriangleMatrix<int> mat1(2);
    TriangleMatrix<int> mat2(2);

    mat1[0][0] = 1; mat2[0][0] = 1;
    EXPECT_TRUE(mat1 == mat2);
}

TEST(TestTriangleMatrix, equality_operator_different) {
    TriangleMatrix<int> mat1(2);
    TriangleMatrix<int> mat2(2);

    mat1[0][0] = 1; mat2[0][0] = 2;
    EXPECT_FALSE(mat1 == mat2);
}

TEST(TestTriangleMatrix, inequality_operator) {
    TriangleMatrix<int> mat1(2);
    TriangleMatrix<int> mat2(2);

    mat1[0][0] = 1; mat2[0][0] = 2;
    EXPECT_TRUE(mat1 != mat2);
}

TEST(TestTriangleMatrix, inequality_operatorSame) {
    TriangleMatrix<int> mat1(2);
    TriangleMatrix<int> mat2(2);

    mat1[0][0] = 1; mat2[0][0] = 1;
    EXPECT_FALSE(mat1 != mat2);
}

TEST(TestTriangleMatrix, assignment_operator) {
    TriangleMatrix<int> mat1(2);
    TriangleMatrix<int> mat2(2);

    mat1[0][0] = 5;
    mat2 = mat1;
    EXPECT_EQ(mat2[0][0], 5);
}

TEST(TestTriangleMatrix, assignment_operator_self) {
    TriangleMatrix<int> mat(2);
    mat[0][0] = 5;
    mat = mat;
    EXPECT_EQ(mat[0][0], 5);
}
