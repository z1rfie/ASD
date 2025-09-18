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

    std::cout << std::endl << "\t �������� � ��������� \t" << std::endl;
    std::cout << std::endl << "������� ���������� ������� � �������� ������� ����� ������: ";
    std::cin >> N1 >> M1;
    Matrix<size_t> first_matrix(N1,M1);
    std::cout << std::endl << "������� �������� �������: ";
    first_matrix.input_matrix();

    system("pause");

    while (1) {
        system("cls");
        std::cout << std::endl << "\t �������� � ��������� \t" << std::endl;
        std::cout << std::endl;
        std::cout << "-- ���� �������: --" << std::endl;
        first_matrix.print_matrix();
        std::cout << std::endl;
        std::cout << "1. ��������" << std::endl;
        std::cout << "2. ���������" << std::endl;
        std::cout << "3. ���������" << std::endl;
        std::cout << "4. ��������� �� ������" << std::endl;
        std::cout << "5. ����������������" << std::endl;
        std::cout << "6. �����" << std::endl;
        std::cout << std::endl;
        std::cout << "�������� �������� (1-6): ";
        std::cin >> choice;
        std::cout << std::endl;

        if (choice == 6) {
            break;
        }

        if (choice < 1 || choice > 6) {
            std::cout << "�������� �����! ���������� �����." << std::endl;
            continue;
        }

        while (1) {
            size_t N2 = 0, M2 = 0;

            if (choice > 0 && choice < 4) {
                std::cout << "������� ���������� ����� � �������� ������ ������� ����� ������: ";
                std::cin >> N2 >> M2;

                if ((choice == 1 || choice == 2) && (N1 != N2 || M1 != M2)) {
                    std::cout << std::endl << "��� ��������/��������� ������� ������ ���� ������ �������! ���������� �����." << std::endl;
                    continue;
                }

                if (choice == 3 && M1 != N2) {
                    std::cout << std::endl << "��� ��������� ���������� �������� ������ ������� ������ ��������� � ����������� ����� ������! ���������� �����." << std::endl;
                    continue;
                }
            }

            int scalar;
            if (choice == 4) {
                std::cout << "������� ������: ";
                std::cin >> scalar;
            }

            Matrix<size_t> second_matrix(N2, M2);

            if (choice > 0 && choice < 4) {
                std::cout << std::endl << "������� �������� ������ �������:" << std::endl;
                second_matrix.input_matrix();
            }

            switch (choice) {
            case 1:
                first_matrix = first_matrix + second_matrix;
                std::cout << std::endl << "��������� ��������:" << std::endl;
                first_matrix.print_matrix();
                break;

            case 2:
                first_matrix = first_matrix - second_matrix;
                std::cout << std::endl << "��������� ���������:" << std::endl;
                first_matrix.input_matrix();
                break;

            case 3:
                first_matrix = first_matrix * second_matrix;
                std::cout << std::endl << "��������� ���������:" << std::endl;
                first_matrix.input_matrix();
                break;
            case 4:
                first_matrix = first_matrix * scalar;
                std::cout << std::endl << "��������� ��������� �� ������:" << std::endl;
                first_matrix.input_matrix();
                break;
            case 5:
                first_matrix.transposition_matrix();
                std::cout << std::endl << "��������� ����������������:" << std::endl;
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