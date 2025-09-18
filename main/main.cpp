#define MATRIX
#ifdef MATRIX

#include "../lib_matrix/matrix.h"
#include <clocale>
#include <iostream>
#include <cstdlib>

int main() {
    setlocale(LC_ALL, "rus");

    int choice;
    size_t N1, M1;

    std::cout << std::endl << "\t ОПЕРАЦИИ С МАТРИЦАМИ \t" << std::endl;
    std::cout << std::endl << "Введите количество строчек и столбцов матрицы через пробел: ";
    std::cin >> N1 >> M1;
    Matrix<size_t> first_matrix(N1,M1);
    std::cout << std::endl << "Введите элементы матрицы: ";
    first_matrix.input_matrix();

    system("pause");

    while (1) {
        system("cls");
        std::cout << std::endl << "\t ОПЕРАЦИИ С МАТРИЦАМИ \t" << std::endl;
        std::cout << std::endl;
        std::cout << "-- Ваша матрица: --" << std::endl;
        first_matrix.print_matrix();
        std::cout << std::endl;
        std::cout << "1. Сложение" << std::endl;
        std::cout << "2. Вычитание" << std::endl;
        std::cout << "3. Умножение" << std::endl;
        std::cout << "4. Умножение на скаляр" << std::endl;
        std::cout << "5. Транспонирование" << std::endl;
        std::cout << "6. Выход" << std::endl;
        std::cout << std::endl;
        std::cout << "Выберите операцию (1-6): ";
        std::cin >> choice;
        std::cout << std::endl;

        if (choice == 6) {
            break;
        }

        if (choice < 1 || choice > 6) {
            std::cout << "Неверный выбор! Попробуйте снова." << std::endl;
            continue;
        }

        while (1) {
            size_t N2 = 0, M2 = 0;

            if (choice > 0 && choice < 4) {
                std::cout << "Введите количество строк и столбцов второй матрицы через пробел: ";
                std::cin >> N2 >> M2;

                if ((choice == 1 || choice == 2) && (N1 != N2 || M1 != M2)) {
                    std::cout << std::endl << "Для сложения/вычитания матрицы должны быть одного размера! Попробуйте снова." << std::endl;
                    continue;
                }

                if (choice == 3 && M1 != N2) {
                    std::cout << std::endl << "Для умножения количество столбцов первой матрицы должно совпадать с количеством строк второй! Попробуйте снова." << std::endl;
                    continue;
                }
            }

            int scalar;
            if (choice == 4) {
                std::cout << "Введите скаляр: ";
                std::cin >> scalar;
            }

            Matrix<size_t> second_matrix(N2, M2);

            if (choice > 0 && choice < 4) {
                std::cout << std::endl << "Введите элементы второй матрицы:" << std::endl;
                second_matrix.input_matrix();
            }

            switch (choice) {
            case 1:
                first_matrix = first_matrix + second_matrix;
                std::cout << std::endl << "Результат сложения:" << std::endl;
                first_matrix.print_matrix();
                break;

            case 2:
                first_matrix = first_matrix - second_matrix;
                std::cout << std::endl << "Результат вычитания:" << std::endl;
                first_matrix.input_matrix();
                break;

            case 3:
                first_matrix = first_matrix * second_matrix;
                std::cout << std::endl << "Результат умножения:" << std::endl;
                first_matrix.input_matrix();
                break;
            case 4:
                first_matrix = first_matrix * scalar;
                std::cout << std::endl << "Результат умножения на скаляр:" << std::endl;
                first_matrix.input_matrix();
                break;
            case 5:
                first_matrix.transposition_matrix();
                std::cout << std::endl << "Результат транспонирования:" << std::endl;
                first_matrix.input_matrix();
                break;
            }

            system("pause");
            break;
        }
    }

    return 0;
}

#endif // MATRIX