#include <windows.h>
#include <iostream>
#include "matrix.h"
#include <gtest/gtest.h>

#define EPSILON 0.000001

TEST(TestMathVectorLib, default_constructor) {
    MathVector<int> vec;

    EXPECT_EQ(vec.data(), nullptr);
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.start_index(), 0);
}

TEST(TestMathVectorLib, size_constructor) {
    MathVector<int> vec(5);

    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec.start_index(), 0);
}

TEST(TestMathVectorLib, size_constructor_big) {
    size_t huge = 1000000;
    MathVector<double> vec(huge);

    EXPECT_EQ(vec.size(), huge);
    EXPECT_EQ(vec.start_index(), 0);
}

TEST(TestMathVectorLib, size_and_index_constructor) {
    MathVector<int> vec(10,5);

    EXPECT_EQ(vec.size(), 10);
    EXPECT_EQ(vec.start_index(), 5);
}

TEST(TestMathVectorLib, size_and_index_constructor_big) {
    size_t huge = 1000000;
    size_t ind = 10000;
    MathVector<double> vec(huge, ind);

    EXPECT_EQ(vec.size(), huge);
    EXPECT_EQ(vec.start_index(), ind);
}

TEST(TestMathVectorLib, size_and_index_constructor_error_index) {
    size_t size = 5;
    size_t index = 50;

    EXPECT_THROW(MathVector<int> vec(size, index), std::runtime_error);
}

TEST(TestMathVectorLib, size_and_index_constructor_error_size) {
    size_t size = 0;
    size_t index = 50;

    EXPECT_THROW(MathVector<int> vec(size, index), std::runtime_error);
}

TEST(TestMathVectorLib, copy_constructor) {
    MathVector<int> vec1(10, 5);
    MathVector<int> vec2(vec1);

    EXPECT_EQ(vec2.size(), 10);
    EXPECT_EQ(vec2.start_index(), 5);
}

TEST(TestMathVectorLib, copy_constructor_big) {
    size_t huge = 10000000;
    size_t ind = 100000;
    MathVector<double> vec1(huge, ind);
    MathVector<double> vec2(huge, ind);

    EXPECT_EQ(vec2.size(), huge);
    EXPECT_EQ(vec2.start_index(), ind);
}

TEST(TestMathVectorLib, operator_addition) {
    MathVector<int> vec1(3);
    MathVector<int> vec2(3);

    vec1[0] = 1; vec1[1] = 2; vec1[2] = 3;
    vec2[0] = 4; vec2[1] = 5; vec2[2] = 6;

    MathVector<int> result = vec1 + vec2;

    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 5);  
    EXPECT_EQ(result[1], 7);  
    EXPECT_EQ(result[2], 9);  
}

TEST(TestMathVectorLib, operator_addition_double) {
    MathVector<double> vec1(2);
    MathVector<double> vec2(2);

    vec1[0] = 1.5; vec1[1] = 2.5;
    vec2[0] = 3.5; vec2[1] = 4.5;

    MathVector<double> result = vec1 + vec2;

    EXPECT_EQ(result[0], 5.0);
    EXPECT_EQ(result[1], 7.0);
}

TEST(TestMathVectorLib, operator_plus_equal) {
    MathVector<int> vec1(3);
    MathVector<int> vec2(3);

    vec1[0] = 1; vec1[1] = 2; vec1[2] = 3;
    vec2[0] = 4; vec2[1] = 5; vec2[2] = 6;

    vec1 += vec2;

    EXPECT_EQ(vec1.size(), 3);
    EXPECT_EQ(vec1[0], 5);
    EXPECT_EQ(vec1[1], 7);
    EXPECT_EQ(vec1[2], 9);
}

TEST(TestMathVectorLib, operator_plus_equal_double) {
    MathVector<double> vec1(2);
    MathVector<double> vec2(2);

    vec1[0] = 1.5; vec1[1] = 2.5;
    vec2[0] = 3.5; vec2[1] = 4.5;

    vec1 += vec2;

    EXPECT_EQ(vec1[0], 5.0);
    EXPECT_EQ(vec1[1], 7.0);
}

TEST(TestMathVectorLib, operator_subtraction) {
    MathVector<int> vec1(3);
    MathVector<int> vec2(3);

    vec1[0] = 1; vec1[1] = 2; vec1[2] = 3;
    vec2[0] = 4; vec2[1] = 5; vec2[2] = 6;

    MathVector<int> result = vec1 - vec2;

    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], -3);
    EXPECT_EQ(result[1], -3);
    EXPECT_EQ(result[2], -3);
}

TEST(TestMathVectorLib, operator_subtraction_double) {
    MathVector<double> vec1(2);
    MathVector<double> vec2(2);

    vec1[0] = 1.5; vec1[1] = 6.7;
    vec2[0] = 3.5; vec2[1] = 4.5;

    MathVector<double> result = vec1 - vec2;

    EXPECT_EQ(result[0], -2.0);
    EXPECT_EQ(result[1], 2.2);
}

TEST(TestMathVectorLib, operator_minus_equal) {
    MathVector<int> vec1(3);
    MathVector<int> vec2(3);

    vec1[0] = 1; vec1[1] = 2; vec1[2] = 3;
    vec2[0] = 4; vec2[1] = 5; vec2[2] = 6;

    vec1 -= vec2;

    EXPECT_EQ(vec1.size(), 3);
    EXPECT_EQ(vec1[0], -3);
    EXPECT_EQ(vec1[1], -3);
    EXPECT_EQ(vec1[2], -3);
}

TEST(TestMathVectorLib, operator_minus_equal_double) {
    MathVector<double> vec1(2);
    MathVector<double> vec2(2);

    vec1[0] = 1.5; vec1[1] = 6.7;
    vec2[0] = 3.5; vec2[1] = 4.5;

    vec1 -= vec2;

    EXPECT_EQ(vec1[0], -2.0);
    EXPECT_EQ(vec1[1], 2.2);
}

TEST(TestMathVectorLib, operator_multiplication_scalar) {
    MathVector<int> vec(3);
    vec[0] = 2; vec[1] = 4; vec[2] = 6;

    MathVector<int> result = vec * 3;

    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 6);
    EXPECT_EQ(result[1], 12);
    EXPECT_EQ(result[2], 18);
}

TEST(TestMathVectorLib, operator_multiplication_scalar_double) {
    MathVector<double> vec(2);
    vec[0] = 1.5; vec[1] = 2.5;

    MathVector<double> result = vec * 2.0;

    EXPECT_EQ(result[0], 3.0);
    EXPECT_EQ(result[1], 5.0);
}

//TEST(TestMathVectorLib, operator_multiplication_scalar_start_index) {
//    MathVector<int> vec(5, 2);
//    vec[2] = 3; vec[3] = 7;
//
//    MathVector<int> result = vec * 4;
//
//    EXPECT_EQ(vec.size(), 5);
//    EXPECT_EQ(vec.start_index(), 2);
//    EXPECT_EQ(vec[2], 12);
//    EXPECT_EQ(vec[3], 28);
//}

TEST(TestMathVectorLib, operator_multiplication_scalar_big) {
    MathVector<int> vec(3);
    vec[0] = 1000000; vec[1] = 2000000; vec[2] = 3000000;

    MathVector<int> result = vec * 1000;

    EXPECT_EQ(result[0], 1000000000);
    EXPECT_EQ(result[1], 2000000000);
}

TEST(TestMathVectorLib, multiply_equal_scalar) {
    MathVector<int> vec(3);
    vec[0] = 2; vec[1] = 4; vec[2] = 6;

    vec *= 3;

    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 6);
    EXPECT_EQ(vec[1], 12);
    EXPECT_EQ(vec[2], 18);
}

TEST(TestMathVectorLib, multiply_equal_scalar_double) {
    MathVector<double> vec(2);
    vec[0] = 1.5; vec[1] = 2.5;

    vec *= 2.0;

    EXPECT_EQ(vec[0], 3.0);
    EXPECT_EQ(vec[1], 5.0);
}

TEST(TestMathVectorLib, multiply_equal_scalar_big) {
    MathVector<int> vec(3);
    vec[0] = 1000000; vec[1] = 2000000; vec[2] = 3000000;

    vec *= 1000;

    EXPECT_EQ(vec[0], 1000000000);
    EXPECT_EQ(vec[1], 2000000000);
}

// продолжить 