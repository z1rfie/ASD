#include <windows.h>
#include <iostream>
#include "matrix.h"
#include <gtest/gtest.h>

#define EPSILON 0.000001

TEST(TestMatrixLib, default_constructor) {
    Matrix<int> mat;

    EXPECT_EQ(mat.get_n(), 0);
    EXPECT_EQ(mat.get_m(), 0);
    EXPECT_EQ(mat.size(), 0);

    EXPECT_TRUE(mat.is_empty());
}

TEST(TestMatrixLib, size_constructor) {
    const size_t N = 3, M = 4;
    Matrix<double> mat(N, M);

    EXPECT_EQ(mat.get_n(), N);
    EXPECT_EQ(mat.get_m(), M);
    EXPECT_EQ(mat.size(), N);
}

//TEST(TestMatrixLib, huge_size_constructor) {
//    const size_t N = 10000, M = 40000;
//    Matrix<double> mat(N, M);
//
//    EXPECT_EQ(mat.get_n(), N);
//    EXPECT_EQ(mat.get_m(), M);
//    EXPECT_EQ(mat.size(), N);
//}

TEST(TestMatrixLib, copy_constructor) {
    Matrix<int> original(2, 3);
    original[0][0] = 1; original[0][1] = 2; original[0][2] = 3;
    original[1][0] = 4; original[1][1] = 5; original[1][2] = 6;

    Matrix<int> copy(original);

    EXPECT_EQ(copy.get_n(), original.get_n());
    EXPECT_EQ(copy.get_m(), original.get_m());

    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 3; j++) {
            EXPECT_EQ(copy[i][j], original[i][j]);
        }
    }
}

TEST(TestMatrixLib, copy_constructor_huge_value) {
    Matrix<int> original(4, 5);

    int value = 100;
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 5; j++) {
            original[i][j] = value++;
        }
    }

    Matrix<int> copy(original);

    EXPECT_EQ(copy.get_n(), original.get_n());
    EXPECT_EQ(copy.get_m(), original.get_m());

    value = 100;
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 5; j++) {
            EXPECT_EQ(copy[i][j], value);
            EXPECT_EQ(copy[i][j], original[i][j]);
            value++;
        }
    }
}

TEST(TestMatrixLib, vector_constructor) {
    MathVector<MathVector<int>> vec;

    MathVector<int> row1(3);
    row1[0] = 1; row1[1] = 2; row1[2] = 3;
    vec.push_back_elem(row1);

    MathVector<int> row2(3);
    row2[0] = 4; row2[1] = 5; row2[2] = 6;
    vec.push_back_elem(row2);

    MathVector<int> row3(3);
    row3[0] = 7; row3[1] = 8; row3[2] = 9;
    vec.push_back_elem(row3);

    Matrix<int> mat(vec);

    EXPECT_EQ(mat.get_n(), 3);
    EXPECT_EQ(mat.get_m(), 3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_EQ(mat[i][j], i * 3 + j + 1);
        }
    }
}

TEST(TestMatrixLib, addition_operator) {
    Matrix<int> mat1(2, 3);
    Matrix<int> mat2(2, 3);

    int value = 1;
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 3; j++) {
            mat1[i][j] = value;
            mat2[i][j] = value * 10;
            value++;
        }
    }

    Matrix<int> result = mat1 + mat2;

    EXPECT_EQ(result.get_n(), 2);
    EXPECT_EQ(result.get_m(), 3);

    value = 1;
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 3; j++) {
            EXPECT_EQ(result[i][j], value + value * 10);
            value++;
        }
    }
}

TEST(TestMatrixLib, addition_with_negative_numbers) {
    Matrix<int> mat1(2, 2);
    Matrix<int> mat2(2, 2);

    mat1[0][0] = 5;  mat1[0][1] = -3;
    mat1[1][0] = -2; mat1[1][1] = 8;

    mat2[0][0] = -1; mat2[0][1] = 4;
    mat2[1][0] = 7;  mat2[1][1] = -6;

    Matrix<int> result = mat1 + mat2;

    EXPECT_EQ(result[0][0], 4);
    EXPECT_EQ(result[0][1], 1);
    EXPECT_EQ(result[1][0], 5);
    EXPECT_EQ(result[1][1], 2);
}

TEST(TestMatrixLib, addition_assignment_operator) {
    Matrix<int> mat1(3, 2);
    Matrix<int> mat2(3, 2);

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 2; j++) {
            mat1[i][j] = i * 2 + j + 1; // 1, 2, 3, 4, 5, 6
            mat2[i][j] = (i * 2 + j + 1) * 2; // 2, 4, 6, 8, 10, 12
        }
    }

    mat1 += mat2;

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 2; j++) {
            int original_value = i * 2 + j + 1;
            EXPECT_EQ(mat1[i][j], original_value + original_value * 2);
        }
    }
}

TEST(TestMatrixLib, addition_assignment_operator_double) {
    Matrix<double> mat1(3, 2);
    Matrix<double> mat2(3, 2);

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 2; j++) {
            mat1[i][j] = i * 2.5 + j + 1.3;
            mat2[i][j] = (i * 2.5 + j + 1.3) * 2;
        }
    }

    mat1 += mat2;

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 2; j++) {
            double original_value = i * 2.5 + j + 1.3;
            EXPECT_DOUBLE_EQ(mat1[i][j], original_value + original_value * 2);
        }
    }
}

TEST(TestMatrixLib, subtraction_operator) {
    Matrix<int> mat1(2, 3);
    Matrix<int> mat2(2, 3);

    int value = 1;
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 3; j++) {
            mat1[i][j] = value;
            mat2[i][j] = value * 10;
            value++;
        }
    }

    Matrix<int> result = mat1 - mat2;

    EXPECT_EQ(result.get_n(), 2);
    EXPECT_EQ(result.get_m(), 3);

    value = 1;
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 3; j++) {
            EXPECT_EQ(result[i][j], value - value * 10);
            value++;
        }
    }
}

TEST(TestMatrixLib, subtraction_with_negative_numbers) {
    Matrix<int> mat1(2, 2);
    Matrix<int> mat2(2, 2);

    mat1[0][0] = 5;  mat1[0][1] = -3;
    mat1[1][0] = -2; mat1[1][1] = 8;

    mat2[0][0] = -1; mat2[0][1] = 4;
    mat2[1][0] = 7;  mat2[1][1] = -6;

    Matrix<int> result = mat1 - mat2;

    EXPECT_EQ(result[0][0], 6);
    EXPECT_EQ(result[0][1], -7);
    EXPECT_EQ(result[1][0], -9);
    EXPECT_EQ(result[1][1], 14);
}

TEST(TestMatrixLib, subtraction_assignment_operator) {
    Matrix<int> mat1(3, 2);
    Matrix<int> mat2(3, 2);

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 2; j++) {
            mat1[i][j] = i * 2 + j + 1; // 1, 2, 3, 4, 5, 6
            mat2[i][j] = (i * 2 + j + 1) * 2; // 2, 4, 6, 8, 10, 12
        }
    }

    mat1 -= mat2;

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 2; j++) {
            int original_value = i * 2 + j + 1;
            EXPECT_EQ(mat1[i][j], original_value - original_value * 2);
        }
    }
}

TEST(TestMatrixLib, subtraction_assignment_operator_double) {
    Matrix<double> mat1(3, 2);
    Matrix<double> mat2(3, 2);

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 2; j++) {
            mat1[i][j] = i * 2.5 + j + 1.3;
            mat2[i][j] = (i * 2.5 + j + 1.3) * 2;
        }
    }

    mat1 -= mat2;

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 2; j++) {
            double original_value = i * 2.5 + j + 1.3;
            EXPECT_DOUBLE_EQ(mat1[i][j], original_value - original_value * 2);
        }
    }
}

TEST(TestMatrixLib, scalar_multiplication_operator) {
    Matrix<int> mat(2, 3);

    int value = 1;
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 3; j++) {
            mat[i][j] = value++;
        }
    }

    Matrix<int> result = mat * 3;

    EXPECT_EQ(result.get_n(), 2);
    EXPECT_EQ(result.get_m(), 3);

    value = 1;
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 3; j++) {
            EXPECT_EQ(result[i][j], value * 3);
            value++;
        }
    }
}

TEST(TestMatrixLib, scalar_multiplication_with_zero) {
    Matrix<int> mat(2, 2);
    mat[0][0] = 5; mat[0][1] = -3;
    mat[1][0] = 2; mat[1][1] = 8;

    Matrix<int> result = mat * 0;

    EXPECT_EQ(result[0][0], 0);
    EXPECT_EQ(result[0][1], 0);
    EXPECT_EQ(result[1][0], 0);
    EXPECT_EQ(result[1][1], 0);
}

TEST(TestMatrixLib, scalar_multiplication_with_negative) {
    Matrix<double> mat(2, 2);
    mat[0][0] = 1.5; mat[0][1] = -2.0;
    mat[1][0] = 3.5; mat[1][1] = 4.0;

    Matrix<double> result = mat * (-2.0);

    EXPECT_DOUBLE_EQ(result[0][0], -3.0);
    EXPECT_DOUBLE_EQ(result[0][1], 4.0);
    EXPECT_DOUBLE_EQ(result[1][0], -7.0);
    EXPECT_DOUBLE_EQ(result[1][1], -8.0);
}

TEST(TestMatrixLib, scalar_multiplication_assignment_operator) {
    Matrix<int> mat(3, 2);

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 2; j++) {
            mat[i][j] = i * 2 + j + 1;
        }
    }

    mat *= 4;

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 2; j++) {
            int original_value = i * 2 + j + 1;
            EXPECT_EQ(mat[i][j], original_value * 4);
        }
    }
}

TEST(TestMatrixLib, scalar_multiplication_assignment_operator_double) {
    Matrix<double> mat(3, 2);

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 2; j++) {
            mat[i][j] = i * 2 + j + 1;
        }
    }

    mat *= 4.7;

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 2; j++) {
            int original_value = i * 2 + j + 1;
            EXPECT_DOUBLE_EQ(mat[i][j], original_value * 4.7);
        }
    }
}

TEST(TestMatrixLib, matrix_vector_multiplication) {
    Matrix<int> mat(2, 3);
    mat[0][0] = 1; mat[0][1] = 2; mat[0][2] = 3;
    mat[1][0] = 4; mat[1][1] = 5; mat[1][2] = 6;

    MathVector<int> vec(3);
    vec[0] = 2; vec[1] = 1; vec[2] = 3;

    MathVector<int> result = mat * vec;

    EXPECT_EQ(result.size(), 2);

    EXPECT_EQ(result[0], 13);
    EXPECT_EQ(result[1], 31);
}

TEST(TestMatrixLib, matrix_vector_multiplication_different_sizes) {
    Matrix<double> mat(3, 2);
    mat[0][0] = 1.5; mat[0][1] = 2.0;
    mat[1][0] = 0.5; mat[1][1] = 1.5;
    mat[2][0] = 2.0; mat[2][1] = 0.5;

    MathVector<double> vec(2);
    vec[0] = 3.0; vec[1] = 2.0;

    MathVector<double> result = mat * vec;

    EXPECT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], 8.5);
    EXPECT_DOUBLE_EQ(result[1], 4.5);
    EXPECT_DOUBLE_EQ(result[2], 7.0);
}

TEST(TestMatrixLib, matrix_matrix_multiplication) {
    Matrix<int> A(2, 3);
    A[0][0] = 1; A[0][1] = 2; A[0][2] = 3;
    A[1][0] = 4; A[1][1] = 5; A[1][2] = 6;

    Matrix<int> B(3, 2);
    B[0][0] = 2; B[0][1] = 1;
    B[1][0] = 3; B[1][1] = 2;
    B[2][0] = 1; B[2][1] = 3;

    Matrix<int> result = A * B;

    EXPECT_EQ(result.get_n(), 2);
    EXPECT_EQ(result.get_m(), 2);

    EXPECT_EQ(result[0][0], 11);
    EXPECT_EQ(result[0][1], 14);
    EXPECT_EQ(result[1][0], 29);
    EXPECT_EQ(result[1][1], 32);
}

TEST(TestMatrixLib, matrix_matrix_multiplication_square) {
    Matrix<int> A(2, 2);
    A[0][0] = 2; A[0][1] = 1;
    A[1][0] = 0; A[1][1] = 3;

    Matrix<int> B(2, 2);
    B[0][0] = 1; B[0][1] = 4;
    B[1][0] = 2; B[1][1] = 1;

    Matrix<int> result = A * B;

    EXPECT_EQ(result.get_n(), 2);
    EXPECT_EQ(result.get_m(), 2);

    EXPECT_EQ(result[0][0], 4);
    EXPECT_EQ(result[0][1], 9);
    EXPECT_EQ(result[1][0], 6);
    EXPECT_EQ(result[1][1], 3);
}

TEST(TestMatrixLib, matrix_matrix_multiplication_large) {
    Matrix<int> A(3, 4);
    int value = 1;
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 4; j++) {
            A[i][j] = value++;
        }
    }

    Matrix<int> B(4, 2);
    value = 5;
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 2; j++) {
            B[i][j] = value++;
        }
    }

    Matrix<int> result = A * B;

    EXPECT_EQ(result.get_n(), 3);
    EXPECT_EQ(result.get_m(), 2);

    EXPECT_EQ(result[0][0], 90);
    EXPECT_EQ(result[1][0], 218);
}

TEST(TestMatrixLib, assignment_operator_matrix) {
    Matrix<int> original(2, 3);
    original[0][0] = 1; original[0][1] = 2; original[0][2] = 3;
    original[1][0] = 4; original[1][1] = 5; original[1][2] = 6;

    Matrix<int> assigned;
    assigned = original;

    EXPECT_EQ(assigned.get_n(), 2);
    EXPECT_EQ(assigned.get_m(), 3);

    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 3; j++) {
            EXPECT_EQ(assigned[i][j], original[i][j]);
        }
    }
}

TEST(TestMatrixLib, self_operator_matrix) {
    Matrix<int> mat(3, 2);
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 2; j++) {
            mat[i][j] = i * 2 + j + 1;
        }
    }

    mat = mat;

    EXPECT_EQ(mat.get_n(), 3);
    EXPECT_EQ(mat.get_m(), 2);

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 2; j++) {
            EXPECT_EQ(mat[i][j], i * 2 + j + 1);
        }
    }
}

TEST(TestMatrixLib, assignment_operator_vector) {
    MathVector<int> vec(4);
    vec[0] = 10; vec[1] = 20; vec[2] = 30; vec[3] = 40;

    Matrix<int> mat;
    mat = vec;

    EXPECT_EQ(mat.get_n(), 4);
    EXPECT_EQ(mat.get_m(), 1);

    for (size_t i = 0; i < 4; i++) {
        EXPECT_EQ(mat[i][0], vec[i]);
    }
}

TEST(TestMatrixLib, assignment_operator_vector_to_existing_matrix) {
    MathVector<int> vec(3);
    vec[0] = 5; vec[1] = 6; vec[2] = 7;

    Matrix<int> mat(2, 2);
    mat[0][0] = 1; mat[0][1] = 2;
    mat[1][0] = 3; mat[1][1] = 4;

    mat = vec;

    EXPECT_EQ(mat.get_n(), 3);
    EXPECT_EQ(mat.get_m(), 1);

    EXPECT_EQ(mat[0][0], 5);
    EXPECT_EQ(mat[1][0], 6);
    EXPECT_EQ(mat[2][0], 7);
}

TEST(TestMatrixLib, assignment_from_empty_vector) {
    MathVector<int> empty_vec;

    Matrix<int> mat;
    mat = empty_vec;

    EXPECT_EQ(mat.get_n(), 0);
    EXPECT_EQ(mat.get_m(), 1);

    EXPECT_TRUE(mat.is_empty());
}

TEST(TestMatrixLib, index_operator_non_const) {
    Matrix<int> mat(2, 3);

    mat[0][0] = 1;
    mat[0][1] = 2;
    mat[0][2] = 3;
    mat[1][0] = 4;
    mat[1][1] = 5;
    mat[1][2] = 6;

    EXPECT_EQ(mat[0][0], 1);
    EXPECT_EQ(mat[0][1], 2);
    EXPECT_EQ(mat[0][2], 3);
    EXPECT_EQ(mat[1][0], 4);
    EXPECT_EQ(mat[1][1], 5);
    EXPECT_EQ(mat[1][2], 6);
}

TEST(TestMatrixLib, index_operator_const) {
    Matrix<int> non_const_mat(2, 2);
    non_const_mat[0][0] = 10;
    non_const_mat[0][1] = 20;
    non_const_mat[1][0] = 30;
    non_const_mat[1][1] = 40;

    const Matrix<int>& const_mat = non_const_mat;

    EXPECT_EQ(const_mat[0][0], 10);
    EXPECT_EQ(const_mat[0][1], 20);
    EXPECT_EQ(const_mat[1][0], 30);
    EXPECT_EQ(const_mat[1][1], 40);
}

TEST(TestMatrixLib, index_operator_edge_cases) {
    Matrix<int> mat(1, 1);

    mat[0][0] = 42;
    EXPECT_EQ(mat[0][0], 42);

    mat[0][0] *= 2;
    EXPECT_EQ(mat[0][0], 84);
}

TEST(TestMatrixLib, transposition_matrix_rectangle) {
    Matrix<int> mat(2, 3);
    mat[0][0] = 1; mat[0][1] = 2; mat[0][2] = 3;
    mat[1][0] = 4; mat[1][1] = 5; mat[1][2] = 6;

    mat.transposition_matrix();

    EXPECT_EQ(mat.get_n(), 3);
    EXPECT_EQ(mat.get_m(), 2);

    EXPECT_EQ(mat[0][0], 1);
    EXPECT_EQ(mat[0][1], 4);
    EXPECT_EQ(mat[1][0], 2);
    EXPECT_EQ(mat[1][1], 5);
    EXPECT_EQ(mat[2][0], 3);
    EXPECT_EQ(mat[2][1], 6);
}

TEST(TestMatrixLib, transposition_matrix_square) {
    Matrix<int> mat(3, 3);

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            mat[i][j] = i * 3 + j + 1;
        }
    }

    mat.transposition_matrix();

    EXPECT_EQ(mat.get_n(), 3);
    EXPECT_EQ(mat.get_m(), 3);

    EXPECT_EQ(mat[0][0], 1);
    EXPECT_EQ(mat[0][1], 4);
    EXPECT_EQ(mat[0][2], 7);
    EXPECT_EQ(mat[1][0], 2);
    EXPECT_EQ(mat[1][1], 5);
    EXPECT_EQ(mat[1][2], 8);
    EXPECT_EQ(mat[2][0], 3);
    EXPECT_EQ(mat[2][1], 6);
    EXPECT_EQ(mat[2][2], 9);
}

TEST(TestMatrixLib, transposition_matrix_single_element) {
    Matrix<int> mat(1, 1);
    mat[0][0] = 42;

    mat.transposition_matrix();

    EXPECT_EQ(mat.get_n(), 1);
    EXPECT_EQ(mat.get_m(), 1);
    EXPECT_EQ(mat[0][0], 42);
}

TEST(TestMatrixLib, transposition_matrix_row_vector) {
    Matrix<int> mat(1, 4);
    mat[0][0] = 1; mat[0][1] = 2; mat[0][2] = 3; mat[0][3] = 4;

    mat.transposition_matrix();
    EXPECT_EQ(mat.get_n(), 4);
    EXPECT_EQ(mat.get_m(), 1);

    EXPECT_EQ(mat[0][0], 1);
    EXPECT_EQ(mat[1][0], 2);
    EXPECT_EQ(mat[2][0], 3);
    EXPECT_EQ(mat[3][0], 4);
}

TEST(TestMatrixLib, transposition_matrix_column_vector) {
    Matrix<int> mat(4, 1);
    mat[0][0] = 1;
    mat[1][0] = 2;
    mat[2][0] = 3;
    mat[3][0] = 4;

    mat.transposition_matrix();

    EXPECT_EQ(mat.get_n(), 1);
    EXPECT_EQ(mat.get_m(), 4);

    EXPECT_EQ(mat[0][0], 1);
    EXPECT_EQ(mat[0][1], 2);
    EXPECT_EQ(mat[0][2], 3);
    EXPECT_EQ(mat[0][3], 4);
}

TEST(TestMatrixLib, double_transposition) {
    Matrix<int> original(2, 3);
    original[0][0] = 1; original[0][1] = 2; original[0][2] = 3;
    original[1][0] = 4; original[1][1] = 5; original[1][2] = 6;

    Matrix<int> mat = original;

    mat.transposition_matrix();
    mat.transposition_matrix();

    EXPECT_EQ(mat.get_n(), original.get_n());
    EXPECT_EQ(mat.get_m(), original.get_m());

    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 3; j++) {
            EXPECT_EQ(mat[i][j], original[i][j]);
        }
    }
}

TEST(TestMatrixLib, at_read) {
    Matrix<int> mat(2, 3);
    mat[0][0] = 1; mat[0][1] = 2; mat[0][2] = 3;
    mat[1][0] = 4; mat[1][1] = 5; mat[1][2] = 6;

    EXPECT_EQ(mat.at(0, 0), 1);
    EXPECT_EQ(mat.at(0, 1), 2);
    EXPECT_EQ(mat.at(0, 2), 3);
    EXPECT_EQ(mat.at(1, 0), 4);
    EXPECT_EQ(mat.at(1, 1), 5);
    EXPECT_EQ(mat.at(1, 2), 6);
}

TEST(TestMatrixLib, at_write) {
    Matrix<int> mat(2, 3);
    mat[0][0] = 1; mat[0][1] = 2; mat[0][2] = 3;
    mat[1][0] = 4; mat[1][1] = 5; mat[1][2] = 6;

    mat.at(0, 1) = 100;
    mat.at(1, 2) = 200;

    EXPECT_EQ(mat.at(0, 1), 100);
    EXPECT_EQ(mat.at(1, 2), 200);
}

TEST(TestMatrixLib, at_const) {
    Matrix<int> mat(2, 3);
    mat[0][0] = 1; mat[0][1] = 2; mat[0][2] = 3;
    mat[1][0] = 4; mat[1][1] = 5; mat[1][2] = 6;

    const Matrix<int>& const_mat = mat;

    EXPECT_EQ(const_mat.at(0, 0), 1);
    EXPECT_EQ(const_mat.at(0, 1), 2);
    EXPECT_EQ(const_mat.at(0, 2), 3);
    EXPECT_EQ(const_mat.at(1, 0), 4);
    EXPECT_EQ(const_mat.at(1, 1), 5);
    EXPECT_EQ(const_mat.at(1, 2), 6);
}

TEST(TestMatrixLib, at_operator_out_of_range) {
    Matrix<int> mat(2, 2);
    mat[0][0] = 1; mat[0][1] = 2;
    mat[1][0] = 3; mat[1][1] = 4;

    EXPECT_THROW(mat.at(2, 0), std::out_of_range);
    EXPECT_THROW(mat.at(0, 2), std::out_of_range);
    EXPECT_THROW(mat.at(2, 2), std::out_of_range);
    EXPECT_THROW(mat.at(10, 10), std::out_of_range);
}

TEST(TestMatrixLib, comparison_operator) {
    Matrix<int> mat1(2, 2);
    mat1[0][0] = 1; mat1[0][1] = 2;
    mat1[1][0] = 3; mat1[1][1] = 4;

    Matrix<int> mat2(2, 2);
    mat2[0][0] = 1; mat2[0][1] = 2;
    mat2[1][0] = 3; mat2[1][1] = 4;

    Matrix<int> mat3(2, 2);
    mat3[0][0] = 1; mat3[0][1] = 2;
    mat3[1][0] = 3; mat3[1][1] = 5;

    Matrix<int> mat4(3, 2);

    EXPECT_TRUE(mat1 == mat2);
    EXPECT_FALSE(mat1 == mat3);
    EXPECT_FALSE(mat1 == mat4);
}

TEST(TestMatrixLib, not_equal_operator) {
    Matrix<int> mat1(2, 2);
    mat1[0][0] = 1; mat1[0][1] = 2;
    mat1[1][0] = 3; mat1[1][1] = 4;

    Matrix<int> mat2(2, 2);
    mat2[0][0] = 1; mat2[0][1] = 2;
    mat2[1][0] = 3; mat2[1][1] = 4;

    Matrix<int> mat3(2, 2);
    mat3[0][0] = 1; mat3[0][1] = 2;
    mat3[1][0] = 3; mat3[1][1] = 5;

    Matrix<int> mat4(3, 2);

    EXPECT_FALSE(mat1 != mat2);
    EXPECT_TRUE(mat1 != mat3);
    EXPECT_TRUE(mat1 != mat4);
}