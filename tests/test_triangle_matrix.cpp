#include <gtest/gtest.h>
#include "triangle_matrix.h"

// Конструкторы
TEST(TriangleMatrix, DefaultConstructor) {
    TriangleMatrix<int> mat;
    EXPECT_EQ(mat.get_n(), 0);
    EXPECT_EQ(mat.get_m(), 0);
}

TEST(TriangleMatrix, SizeConstructor) {
    TriangleMatrix<int> mat(3);
    EXPECT_EQ(mat.get_n(), 3);
    EXPECT_EQ(mat.get_m(), 3);
}

// Оператор []
TEST(TriangleMatrix, IndexOperator) {
    TriangleMatrix<int> mat(2);
    mat[0][0] = 1;
    mat[0][1] = 2;
    mat[1][1] = 3;

    EXPECT_EQ(mat[0][0], 1);
    EXPECT_EQ(mat[0][1], 2);
    EXPECT_EQ(mat[1][1], 3);
}

TEST(TriangleMatrix, ConstIndexOperator) {
    TriangleMatrix<int> mat(2);
    mat[0][0] = 5;
    const TriangleMatrix<int>& const_mat = mat;
    EXPECT_EQ(const_mat[0][0], 5);
}

// Метод at
TEST(TriangleMatrix, AtMethod) {
    TriangleMatrix<int> mat(2);
    mat.at(0, 0) = 5;
    EXPECT_EQ(mat.at(0, 0), 5);
}

TEST(TriangleMatrix, AtMethodOutOfRange) {
    TriangleMatrix<int> mat(2);
    EXPECT_THROW(mat.at(5, 5), std::out_of_range);
}

// Оператор +
TEST(TriangleMatrix, Addition) {
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

// Оператор +=
TEST(TriangleMatrix, AdditionAssignment) {
    TriangleMatrix<int> mat1(2);
    TriangleMatrix<int> mat2(2);

    mat1[0][0] = 1; mat1[0][1] = 2;
    mat2[0][0] = 3; mat2[0][1] = 4;

    mat1 += mat2;
    EXPECT_EQ(mat1[0][0], 4);
    EXPECT_EQ(mat1[0][1], 6);
}

TEST(TriangleMatrix, AdditionAssignmentSelf) {
    TriangleMatrix<int> mat(2);
    mat[0][0] = 1;
    mat += mat;
    EXPECT_EQ(mat[0][0], 2);
}

// Оператор -
TEST(TriangleMatrix, Subtraction) {
    TriangleMatrix<int> mat1(2);
    TriangleMatrix<int> mat2(2);

    mat1[0][0] = 5; mat1[0][1] = 7;
    mat2[0][0] = 2; mat2[0][1] = 3;

    TriangleMatrix<int> result = mat1 - mat2;
    EXPECT_EQ(result[0][0], 3);
    EXPECT_EQ(result[0][1], 4);
}

TEST(TriangleMatrix, SubtractionNegativeResult) {
    TriangleMatrix<int> mat1(2);
    TriangleMatrix<int> mat2(2);

    mat1[0][0] = 1;
    mat2[0][0] = 3;

    TriangleMatrix<int> result = mat1 - mat2;
    EXPECT_EQ(result[0][0], -2);
}

// Оператор -=
TEST(TriangleMatrix, SubtractionAssignment) {
    TriangleMatrix<int> mat1(2);
    TriangleMatrix<int> mat2(2);

    mat1[0][0] = 10;
    mat2[0][0] = 3;

    mat1 -= mat2;
    EXPECT_EQ(mat1[0][0], 7);
}

TEST(TriangleMatrix, SubtractionAssignmentZero) {
    TriangleMatrix<int> mat(2);
    mat[0][0] = 5;
    mat -= mat;
    EXPECT_EQ(mat[0][0], 0);
}

// Оператор * (скаляр)
TEST(TriangleMatrix, ScalarMultiplication) {
    TriangleMatrix<int> mat(2);
    mat[0][0] = 2; mat[0][1] = 3;
    mat[1][1] = 4;

    TriangleMatrix<int> result = mat * 3;
    EXPECT_EQ(result[0][0], 6);
    EXPECT_EQ(result[0][1], 9);
    EXPECT_EQ(result[1][1], 12);
}

TEST(TriangleMatrix, ScalarMultiplicationZero) {
    TriangleMatrix<int> mat(2);
    mat[0][0] = 5;
    TriangleMatrix<int> result = mat * 0;
    EXPECT_EQ(result[0][0], 0);
}

// Оператор *= (скаляр)
TEST(TriangleMatrix, ScalarMultiplicationAssignment) {
    TriangleMatrix<int> mat(2);
    mat[0][0] = 2;
    mat *= 4;
    EXPECT_EQ(mat[0][0], 8);
}

TEST(TriangleMatrix, ScalarMultiplicationAssignmentOne) {
    TriangleMatrix<int> mat(2);
    mat[0][0] = 5;
    mat *= 1;
    EXPECT_EQ(mat[0][0], 5);
}

// Оператор * (матрица)
TEST(TriangleMatrix, MatrixMultiplication) {
    TriangleMatrix<int> mat1(2);
    TriangleMatrix<int> mat2(2);

    mat1[0][0] = 1; mat1[0][1] = 2;
    mat1[1][1] = 3;

    mat2[0][0] = 4; mat2[0][1] = 5;
    mat2[1][1] = 6;

    TriangleMatrix<int> result = mat1 * mat2;
    EXPECT_EQ(result[0][0], 4);   // 1*4
    EXPECT_EQ(result[0][1], 17);  // 1*5 + 2*6
    EXPECT_EQ(result[1][1], 18);  // 3*6
}

TEST(TriangleMatrix, MatrixMultiplicationIdentity) {
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

// Оператор * (вектор)
TEST(TriangleMatrix, VectorMultiplication) {
    TriangleMatrix<int> mat(2);
    MathVector<int> vec(2);

    mat[0][0] = 1; mat[0][1] = 2;
    mat[1][1] = 3;

    vec[0] = 4; vec[1] = 5;

    MathVector<int> result = mat * vec;
    EXPECT_EQ(result[0], 14);  // 1*4 + 2*5
    EXPECT_EQ(result[1], 15);  // 3*5
}

TEST(TriangleMatrix, VectorMultiplicationWrongSize) {
    TriangleMatrix<int> mat(2);
    MathVector<int> vec(3);
    EXPECT_THROW(mat * vec, std::invalid_argument);
}

// Оператор ==
TEST(TriangleMatrix, EqualityOperator) {
    TriangleMatrix<int> mat1(2);
    TriangleMatrix<int> mat2(2);

    mat1[0][0] = 1; mat2[0][0] = 1;
    EXPECT_TRUE(mat1 == mat2);
}

TEST(TriangleMatrix, EqualityOperatorDifferent) {
    TriangleMatrix<int> mat1(2);
    TriangleMatrix<int> mat2(2);

    mat1[0][0] = 1; mat2[0][0] = 2;
    EXPECT_FALSE(mat1 == mat2);
}

// Оператор !=
TEST(TriangleMatrix, InequalityOperator) {
    TriangleMatrix<int> mat1(2);
    TriangleMatrix<int> mat2(2);

    mat1[0][0] = 1; mat2[0][0] = 2;
    EXPECT_TRUE(mat1 != mat2);
}

TEST(TriangleMatrix, InequalityOperatorSame) {
    TriangleMatrix<int> mat1(2);
    TriangleMatrix<int> mat2(2);

    mat1[0][0] = 1; mat2[0][0] = 1;
    EXPECT_FALSE(mat1 != mat2);
}

// Оператор =
TEST(TriangleMatrix, AssignmentOperator) {
    TriangleMatrix<int> mat1(2);
    TriangleMatrix<int> mat2(2);

    mat1[0][0] = 5;
    mat2 = mat1;
    EXPECT_EQ(mat2[0][0], 5);
}

TEST(TriangleMatrix, AssignmentOperatorSelf) {
    TriangleMatrix<int> mat(2);
    mat[0][0] = 5;
    mat = mat;
    EXPECT_EQ(mat[0][0], 5);
}
