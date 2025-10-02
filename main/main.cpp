#define MATRIX
#ifdef MATRIX

#include "../lib_matrix/matrix.h"
#include "../lib_triangle_matrix/triangle_matrix.h"
#include <iostream>
#include <cstdlib>

void triangular_matrices_menu();
void vectors_menu();
void regular_matrix_operations_menu();
template<typename T>
void regular_multiplication_menu(Matrix<T>& matrix);
template<typename T>
void triangular_multiplication_menu(TriangleMatrix<T>& matrix);

int main() {
    int main_choice;

    while (true) {
        system("cls");
        std::cout << std::endl << "\t MATRIX CALCULATOR \t" << std::endl;
        std::cout << std::endl;
        std::cout << "Choose matrix type:" << std::endl;
        std::cout << "1. Regular matrices" << std::endl;
        std::cout << "2. Triangular matrices" << std::endl;
        std::cout << "3. Vectors" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << std::endl;
        std::cout << "Choose type (1-4): ";
        std::cin >> main_choice;

        switch (main_choice) {
        case 1: regular_matrix_operations_menu(); break;
        case 2: triangular_matrices_menu(); break;
        case 3: vectors_menu(); break;
        case 4: return 0;
        default:
            std::cout << "Incorrect choice! Try again." << std::endl;
            system("pause");
        }
    }
}

void regular_matrix_operations_menu() {
    int choice;
    size_t N1, M1;
    system("cls");
    std::cout << std::endl << "\t MATRIX OPERATIONS \t" << std::endl;
    std::cout << std::endl << "Enter the number of matrix rows and columns separated by spaces: ";
    std::cin >> N1 >> M1;
    Matrix<int> first_matrix(N1, M1);
    std::cout << std::endl << "Enter the matrix elements: " << std::endl;
    first_matrix.input_matrix(N1,M1);

    system("pause");

    while (1) {
        system("cls");
        std::cout << std::endl << "\t MATRIX OPERATIONS \t" << std::endl;
        std::cout << std::endl << "-- Your matrix: --" << std::endl;
        first_matrix.print_matrix();
        std::cout << std::endl;
        std::cout << "1. Addition" << std::endl;
        std::cout << "2. Subtraction" << std::endl;
        std::cout << "3. Multiplication" << std::endl;
        std::cout << "4. Transpose" << std::endl;
        std::cout << "5. Back" << std::endl;
        std::cout << std::endl;
        std::cout << "Choose operation (1-5): ";
        std::cin >> choice;

        if (choice == 5) break;
        if (choice < 1 || choice > 5) {
            std::cout << "Incorrect choice! Try again." << std::endl;
            system("pause");
            continue;
        }

		while (1) {
			size_t N2 = 0, M2 = 0;
			if (choice > 0 && choice < 3) {
				std::cout << "Enter the number of rows and columns of the second matrix, separated by spaces: ";
				std::cin >> N2 >> M2;

				if ((choice == 1 || choice == 2) && (first_matrix.get_n() != N2 || first_matrix.get_m() != M2)) {
					std::cout << std::endl << "For addition/subtraction, matrices must be the same size! Try again." << std::endl;
					continue;
				}
			}

			Matrix<int> second_matrix(N2, M2);

			if (choice > 0 && choice < 3) {
				std::cout << std::endl << "Enter the elements of the second matrix:" << std::endl;
				second_matrix.input_matrix(N2,M2);
			}

			switch (choice) {
			case 1:
                first_matrix = first_matrix + second_matrix;
				std::cout << std::endl << "Result of addition:" << std::endl;
				break;

			case 2:
				first_matrix = first_matrix - second_matrix;
				std::cout << std::endl << "Result of subtraction:" << std::endl;
				break;

			case 3:
                regular_multiplication_menu(first_matrix);
				break;
			case 4:
				first_matrix.transposition_matrix();
				std::cout << std::endl << "Transposition result:" << std::endl;
				break;
			}
			first_matrix.print_matrix();
			system("pause");
			break;
		}
    }
}

template<typename T>
void regular_multiplication_menu(Matrix<T>& matrix) {
    int choice;
    size_t N = matrix.get_n();
    size_t M = matrix.get_m();

    system("cls");
    std::cout << std::endl << "\t MULTIPLICATION \t" << std::endl;
    std::cout << std::endl;
    std::cout << "1. Multiply by scalar" << std::endl;
    std::cout << "2. Multiply by vector" << std::endl;
    std::cout << "3. Multiply by matrix" << std::endl;
    std::cout << "4. Back" << std::endl;
    std::cout << std::endl;
    std::cout << "Choose option (1-4): ";
    std::cin >> choice;

    if (choice == 4) return;

    switch (choice) {
    case 1:
        int scalar;
        std::cout << "Enter scalar: ";
        std::cin >> scalar;
        matrix = matrix * scalar;
        break;
    case 2: {
        size_t vector_size;
        while (1) {
            std::cout << "Enter vector size: ";
            std::cin >> vector_size;

            if (M == vector_size) {
                break;
            }

            std::cout << "Matrix columns (" << M << ") must match vector size (" << vector_size << ")!" << std::endl;
            std::cout << "Please try again." << std::endl;
        }

        MathVector<int> vector(vector_size);

        std::cout << "Enter vector elements:" << std::endl;
        vector.input_vector();

        matrix = matrix * vector;
        break;
    }
	case 3: 
		size_t N2, M2;

		while (1) {
			std::cout << "Enter second matrix rows and columns: ";
			std::cin >> N2 >> M2;

			if (M != N2) {
				std::cout << std::endl << "For multiplication, the number of columns of the first matrix must match the number of rows of the second! Try again." << std::endl;
				continue;
			}
			else break;
		}

		Matrix<int> second_matrix(N2, M2);
		second_matrix.input_matrix(N2,M2);
		matrix = matrix * second_matrix;
		break;
    }
}

void triangular_matrices_menu() {
    int choice;
    size_t first_size;
    system("cls");
    std::cout << std::endl << "\t TRIANGLE MATRIX OPERATIONS \t" << std::endl;
    std::cout << std::endl << "Enter the size of the triangular matrix: ";
    std::cin >> first_size;
    TriangleMatrix<size_t> first_matrix(first_size);
    std::cout << std::endl << "Enter the matrix elements: ";
    first_matrix.input_triangle();

    system("pause");

    while (1) {
        system("cls");
        std::cout << std::endl << "\t TRIANGLE MATRIX OPERATIONS \t" << std::endl;
        std::cout << std::endl << "-- Your matrix: --" << std::endl;
        first_matrix.print_triangle();
        std::cout << std::endl;
        std::cout << "1. Addition" << std::endl;
        std::cout << "2. Subtraction" << std::endl;
        std::cout << "3. Multiplication" << std::endl;
        std::cout << "4. Transpose" << std::endl;
        std::cout << "5. Back" << std::endl;
        std::cout << std::endl;
        std::cout << "Choose operation (1-5): ";
        std::cin >> choice;

        if (choice == 5) break;
        if (choice < 1 || choice > 5) {
            std::cout << "Incorrect choice! Try again." << std::endl;
            system("pause");
            continue;
        }

        while (1) {
            size_t second_size = 0;
            if (choice > 0 && choice < 3) {
                std::cout << "Enter the size of the second triangular matrix: ";
                std::cin >> second_size;

                if ((choice == 1 || choice == 2) && (first_size != second_size)) {
                    std::cout << std::endl << "For addition/subtraction, matrices must be the same size! Try again." << std::endl;
                    continue;
                }
            }

            TriangleMatrix<size_t> second_matrix(second_size);

            if (choice > 0 && choice < 3) {
                std::cout << std::endl << "Enter the elements of the second matrix:" << std::endl;
                second_matrix.input_triangle();
            }

            switch (choice) {
            case 1:
                first_matrix = first_matrix + second_matrix;
                std::cout << std::endl << "Result of addition:" << std::endl;
                first_matrix.print_triangle();
                system("pause");
                break;
            case 2:
                first_matrix = first_matrix - second_matrix;
                std::cout << std::endl << "Result of subtraction:" << std::endl;
                first_matrix.print_triangle();
                system("pause");
                break;
            case 3:
                triangular_multiplication_menu(first_matrix);
                break;
            case 4:
                first_matrix.transposition_matrix();
                std::cout << std::endl << "Transposition result:" << std::endl;
                first_matrix.print_triangle();
                system("pause");
                break;
            }
            /*first_matrix.print_matrix();
            system("pause");*/
            break;
        }
    }
}

// the problem of redundant functions

template<typename T>
void triangular_multiplication_menu(TriangleMatrix<T>& matrix) {
    int choice;
    size_t first_size = matrix.get_size();

    system("cls");
    std::cout << std::endl << "\t MULTIPLICATION \t" << std::endl;
    std::cout << std::endl;
    std::cout << "1. Multiply by scalar" << std::endl;
    std::cout << "2. Multiply by vector" << std::endl;
    std::cout << "3. Multiply by matrix" << std::endl;
    std::cout << "4. Back" << std::endl;
    std::cout << std::endl;
    std::cout << "Choose option (1-4): ";
    std::cin >> choice;

    if (choice == 4) return;

    switch (choice) {
    case 1: {
        int scalar;
        std::cout << "Enter scalar: ";
        std::cin >> scalar;
        matrix = matrix * scalar;
        break;
    }
    case 2: {
        size_t vector_size;
        while (1) {
            std::cout << "Enter vector size: ";
            std::cin >> vector_size;

            if (first_size == vector_size) {
                break;
            }

            std::cout << "Matrix size (" << first_size << ") must match vector size (" << vector_size << ")!" << std::endl;
            std::cout << "Please try again." << std::endl;
        }

        MathVector<size_t> vector(vector_size);
        std::cout << "Enter vector elements:" << std::endl;
        vector.input_vector();
        matrix = matrix * vector;
        break;
    }
    case 3: {
        size_t second_size;

        while (1) {
            std::cout << "Enter second matrix size: ";
            std::cin >> second_size;

            if (first_size != second_size) {
                std::cout << std::endl << "The size of the first matrix must match the size of the second matrix. Try again." << std::endl;
                continue;
            }
            else break;
        }

        TriangleMatrix<size_t> second_matrix(second_size);
        second_matrix.input_triangle();
        matrix = matrix * second_matrix;
        break;
    }

    }
    system("pause");
}

void vectors_menu() {
    std::cout << "Vectors menu - coming soon!" << std::endl;
    system("pause");
}

#endif // MATRIX