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

    EXPECT_DOUBLE_EQ(result[0], 5.0);
    EXPECT_DOUBLE_EQ(result[1], 7.0);
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

    EXPECT_DOUBLE_EQ(vec1[0], 5.0);
    EXPECT_DOUBLE_EQ(vec1[1], 7.0);
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

    EXPECT_DOUBLE_EQ(result[0], -2.0);
    EXPECT_DOUBLE_EQ(result[1], 2.2);
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

    EXPECT_DOUBLE_EQ(vec1[0], -2.0);
    EXPECT_DOUBLE_EQ(vec1[1], 2.2);
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

    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 5.0);
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

    EXPECT_DOUBLE_EQ(vec[0], 3.0);
    EXPECT_DOUBLE_EQ(vec[1], 5.0);
}

TEST(TestMathVectorLib, multiply_equal_scalar_big) {
    MathVector<int> vec(3);
    vec[0] = 1000000; vec[1] = 2000000; vec[2] = 3000000;

    vec *= 1000;

    EXPECT_EQ(vec[0], 1000000000);
    EXPECT_EQ(vec[1], 2000000000);
}

TEST(TestMathVectorLib, scalar_product) {
    MathVector<int> vec1(3);
    MathVector<int> vec2(3);

    vec1[0] = 1; vec1[1] = 2; vec1[2] = 3;
    vec2[0] = 4; vec2[1] = 5; vec2[2] = 6;

    int result = vec1 * vec2;
    int expected = 32; 

    EXPECT_EQ(result, expected);
}

TEST(TestMathVectorLib, scalar_product_zero) {
    MathVector<double> vec1(4);
    MathVector<double> vec2(4);

    vec1[0] = 1.5; vec1[1] = 0.0; vec1[2] = 2.5; vec1[3] = 0.0;
    vec2[0] = 0.0; vec2[1] = 3.0; vec2[2] = 0.0; vec2[3] = 4.0;

    double result = vec1 * vec2;
    double expected = 0.0; 

    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(TestMathVectorLib, scalar_product_negative) {
    MathVector<int> vec1(3);
    MathVector<int> vec2(3);

    vec1[0] = -2; vec1[1] = 3; vec1[2] = -1;
    vec2[0] = 4; vec2[1] = -2; vec2[2] = 5;

    int result = vec1 * vec2;
    int expected = -19;

    EXPECT_EQ(result, expected);
}

TEST(TestMathVectorLib, square_bracket_operator) {
    MathVector<int> vec(3);

    vec[0] = 10;
    vec[1] = 20;
    vec[2] = 30;

    EXPECT_EQ(vec[0], 10);
    EXPECT_EQ(vec[1], 20);
    EXPECT_EQ(vec[2], 30);

    vec[1] = 25;
    EXPECT_EQ(vec[1], 25);
}

//TEST(TestMathVectorLib, square_bracket_operator_error) {
//    MathVector<double> vec(3);
//
//    EXPECT_NO_THROW(vec[0]);
//    EXPECT_NO_THROW(vec[2]);
//
//    EXPECT_THROW(vec[3], std::out_of_range);
//    EXPECT_THROW(vec[100], std::out_of_range);
//}

TEST(TestMathVectorLib, equals_operator) {
    MathVector<int> vec1(3);
    MathVector<int> vec2(3);

    vec1[0] = 1; vec1[1] = 2; vec1[2] = 3;
    vec2[0] = 4; vec2[1] = 5; vec2[2] = 6;

    vec1 = vec2;

    for (size_t i = 0; i < 3; i++) {
        EXPECT_EQ(vec1[i], vec2[i]);
    }
}

TEST(TestMathVectorLib, equals_operator_self_assignment) {
    MathVector<int> vec1(3);
    vec1[0] = 1; vec1[1] = 2; vec1[2] = 3;

    vec1 = vec1;

    for (size_t i = 0; i < 3; i++) {
        EXPECT_EQ(vec1[i], i + 1);
    }
}

TEST(TestMathVectorLib, equals_operator_different_sizes) {
    MathVector<int> vec1(2);
    MathVector<int> vec2(5);

    vec1[0] = 10; vec1[1] = 20;
    vec2[0] = 1; vec2[1] = 2; vec2[2] = 3; vec2[3] = 4; vec2[4] = 5;

    vec1 = vec2;

    EXPECT_EQ(vec1.size(), 5);
    for (size_t i = 0; i < 5; i++) {
        EXPECT_EQ(vec1[i], vec2[i]);
    }
}

TEST(TestMathVectorLib, equals_operator_different_start_index) {
    MathVector<int> vec1(3, 0); 
    MathVector<int> vec2(3, 5);

    vec1[0] = 10; vec1[1] = 20; vec1[2] = 30;
    vec2[5] = 100; vec2[6] = 200; vec2[7] = 300;

    vec1 = vec2;

    EXPECT_EQ(vec1.start_index(), 5);
    EXPECT_EQ(vec1[5], 100);
    EXPECT_EQ(vec1[6], 200);
    EXPECT_EQ(vec1[7], 300);
}

//TEST(TestMathVectorLib, output_operator) {
//    MathVector<int> vec(3);
//    vec[0] = 1; vec[1] = 2; vec[2] = 3;
//
//    std::ostringstream oss;
//    oss << vec;
//
//    EXPECT_EQ(oss.str(), "[1, 2, 3]");
//}
//
//TEST(TestMathVectorLib, output_operator_one_elem) {
//    MathVector<int> vec(1);
//    vec[0] = 42;
//
//    std::ostringstream oss;
//    oss << vec;
//
//    EXPECT_EQ(oss.str(), "[42]");
//}
//
//TEST(TestMathVectorLib, output_operator_empty_vec) {
//    MathVector<int> vec(0);
//
//    std::ostringstream oss;
//    oss << vec;
//
//    EXPECT_EQ(oss.str(), "[]");
//}
//
//TEST(TestMathVectorLib, output_operator_start_index) {
//    MathVector<int> vec(2, 5);
//    vec[5] = 10; vec[6] = 20;
//
//    std::ostringstream oss;
//    oss << vec;
//
//    EXPECT_EQ(oss.str(), "[10, 20]");
//}
//
//TEST(TestMathVectorLib, output_operator_double) {
//    MathVector<double> vec(2);
//    vec[0] = 3.14; vec[1] = 2.71;
//
//    std::ostringstream oss;
//    oss << vec;
//
//    EXPECT_EQ(oss.str(), "[3.14, 2.71]");
//}

TEST(TestMathVectorLib, input_operator) {
    MathVector<int> vec(3);

    std::istringstream iss("10 20 30");
    iss >> vec;

    EXPECT_EQ(vec[0], 10);
    EXPECT_EQ(vec[1], 20);
    EXPECT_EQ(vec[2], 30);
}

TEST(TestMathVectorLib, input_operator_start_index) {
    MathVector<int> vec(2, 3);

    std::istringstream iss("100 200");
    iss >> vec;

    EXPECT_EQ(vec[3], 100);
    EXPECT_EQ(vec[4], 200);
}

TEST(TestMathVectorLib, input_operator_double) {
    MathVector<double> vec(2);

    std::istringstream iss("1.5 2.5");
    iss >> vec;

    EXPECT_DOUBLE_EQ(vec[0], 1.5);
    EXPECT_DOUBLE_EQ(vec[1], 2.5);
}

TEST(TestMathVectorLib, at) {
    MathVector<int> vec(3);
    vec[0] = 10; vec[1] = 20; vec[2] = 30;

    EXPECT_EQ(vec.at(0), 10);
    EXPECT_EQ(vec.at(1), 20);
    EXPECT_EQ(vec.at(2), 30);
}

TEST(TestMathVectorLib, at_write) {
    MathVector<int> vec(2);

    vec.at(0) = 100;
    vec.at(1) = 200;

    EXPECT_EQ(vec[0], 100);
    EXPECT_EQ(vec[1], 200);
}

TEST(TestMathVectorLib, at_start_index) {
    MathVector<int> vec(2, 5);

    vec.at(5) = 50;
    vec.at(6) = 60;

    EXPECT_EQ(vec[5], 50);
    EXPECT_EQ(vec[6], 60);
}

TEST(TestMathVectorLib, at_error) {
    MathVector<int> vec(3);

    EXPECT_NO_THROW(vec.at(0));
    EXPECT_NO_THROW(vec.at(2));

    EXPECT_THROW(vec.at(3), std::out_of_range);
    EXPECT_THROW(vec.at(100), std::out_of_range);
    EXPECT_THROW(vec.at(-1), std::out_of_range);
}

TEST(TestMathVectorLib, comparison_operator) {
    MathVector<int> vec1(3);
    MathVector<int> vec2(3);

    vec1[0] = 1; vec1[1] = 2; vec1[2] = 3;
    vec2[0] = 1; vec2[1] = 2; vec2[2] = 3;

    EXPECT_TRUE(vec1 == vec2);
    EXPECT_FALSE(vec1 != vec2);
}

TEST(TestMathVectorLib, comparison_operator_different_size) {
    MathVector<int> vec1(3);
    MathVector<int> vec2(2);

    vec1[0] = 1; vec1[1] = 2; vec1[2] = 3;
    vec2[0] = 1; vec2[1] = 2;

    EXPECT_FALSE(vec1 == vec2);
}

TEST(TestMathVectorLib, comparison_operator_start_index) {
    MathVector<int> vec1(3, 0);
    MathVector<int> vec2(3, 1);

    vec1[0] = 1; vec1[1] = 2; vec1[2] = 3;
    vec2[1] = 1; vec2[2] = 2; vec2[3] = 3;

    EXPECT_FALSE(vec1 == vec2);
}

TEST(TestMathVectorLib, comparison_operator_different_data) {
    MathVector<int> vec1(3);
    MathVector<int> vec2(3);

    vec1[0] = 1; vec1[1] = 2; vec1[2] = 3;
    vec2[0] = 1; vec2[1] = 9; vec2[2] = 3;

    EXPECT_FALSE(vec1 == vec2);
}

TEST(TestMathVectorLib, comparison_operator_empty_vectors) {
    MathVector<int> vec1(0);
    MathVector<int> vec2(0);

    EXPECT_TRUE(vec1 == vec2);
}

TEST(TestMathVectorLib, comparison_operator_self) {
    MathVector<int> vec1(2);
    vec1[0] = 5; vec1[1] = 10;

    EXPECT_TRUE(vec1 == vec1);
}

TEST(TestMathVectorLib, not_equal_operator) {
    MathVector<int> vec1(2);
    MathVector<int> vec2(2);

    vec1[0] = 1; vec1[1] = 2;
    vec2[0] = 1; vec2[1] = 3;

    EXPECT_TRUE(vec1 != vec2);
    EXPECT_FALSE(vec1 == vec2);
}