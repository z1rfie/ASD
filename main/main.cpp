//#define EASY_EXAMPLE
#define MATRIX
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"

int main() {
  int a, b;
  float result;

  a = 1; b = 4;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  a = 1; b = 0;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  return 0;
}

#endif  // EASY_EXAMPLE

#ifdef MATRIX

#include "../lib_matrix/matrix.h"
#include <clocale>
#include <iostream>

int main() {
    setlocale(LC_ALL, "rus");

    int choice;

    while (1) {
        std::cout << std::endl << "\t ОПЕРАЦИИ С МАТРИЦАМИ \t" << std::endl;
        std::cout << std::endl;
        std::cout << "1. Сложение" << std::endl;
        std::cout << "2. Вычитание" << std::endl;
        std::cout << "3. Умножение" << std::endl;
        std::cout << "4. Выход" << std::endl;
        std::cout << std::endl;
        std::cout << "Выберите операцию (1-4): ";
        std::cin >> choice;
        std::cout << std::endl;

        if (choice == 4) {
            break;
        }

        if (choice < 1 || choice > 4) {
            std::cout << "Неверный выбор! Попробуйте снова." << std::endl;
            continue;
        }

        while (1) {
            size_t N1, M1;
            std::cout << "Введите количество строк и столбцов для первой матрицы через пробел: ";
            std::cin >> N1 >> M1;

            size_t N2, M2;
            std::cout << "Введите количество строк и столбцов для второй матрицы через пробел: ";
            std::cin >> N2 >> M2;

            if ((choice == 1 || choice == 2) && (N1 != N2 || M1 != M2)) {
                std::cout << std::endl << "Для сложения/вычитания матрицы должны быть одного размера! Попробуйте снова." << std::endl;
                std::cout << std::endl;
                continue;
            }

            if (choice == 3 && M1 != N2) {
                std::cout << std::endl << "Для умножения количество столбцов первой матрицы должно совпадать с количеством строк второй! Попробуйте снова." << std::endl;
                std::cout << std::endl;
                continue;
            }

            Matrix<size_t> first_matrix(N1, M1);
            Matrix<size_t> second_matrix(N2, M2);
            Matrix<size_t> result;

            std::cout << std::endl << "Введите элементы первой матрицы:" << std::endl;
            first_matrix.input_matrix();

            std::cout << std::endl << "Введите элементы второй матрицы:" << std::endl;
            second_matrix.input_matrix();

            switch (choice) {
            case 1: 
                result = first_matrix + second_matrix;
                std::cout << std::endl << "Результат сложения:" << std::endl;
                result.print_matrix();
                break;

            case 2: 
                result = first_matrix - second_matrix;
                std::cout << std::endl << "Результат вычитания:" << std::endl;
                result.input_matrix();
                break;

            case 3: 
                result = first_matrix * second_matrix;
                std::cout << std::endl << "Результат умножения:" << std::endl;
                result.input_matrix();
                break;
            }

            break;
        }
    }

    return 0;
}

#endif // MATRIX