#define ALGORITHMS
#ifdef ALGORITHMS
#include "../lib_matrix/matrix.h"
#include "../lib_stack/stack.h"
#include "../lib_list/list.h"
#include <iostream>

bool check_breckets(std::string str);

void read_expression(std::string expression);

template<typename T>
bool is_looped(List<T>& list) {
    List<T>::Iterator it1 = list.begin();
    List<T>::Iterator it2 = list.begin();

    ++it2;
    while (it2 != list.end()) {
        if (it1 == it2) {
            return true;
        }
        ++it1;
        ++it2; ++it2;
    }

    return false;
}

template<typename T>
T find_local_min(const Matrix<T>& matr, size_t start_i, size_t start_j) {
    if (matr.get_n() != matr.get_m()) {
        throw std::logic_error("Matrix must be square!");
    }
    if (start_i >= matr.get_n() || start_j >= matr.get_n()) {
        throw std::out_of_range("Start position out of matrix bounds!");
    }

    size_t i = start_i;
    size_t j = start_j;

    int di[] = { -1, 1, 0, 0 };
    int dj[] = { 0, 0, -1, 1 };

    while (1) {
        T current_val = matr[i][j];
        size_t best_i = i;
        size_t best_j = j;
        T best_val = current_val;

        for (int dir = 0; dir < 4; dir++) {
            int ni = i + di[dir];
            int nj = j + dj[dir];

            if (ni >= 0 && ni < matr.get_n() && nj >= 0 && nj < matr.get_n()) {
                T neighbor_val = matr[ni][nj];
                if (neighbor_val < best_val) {
                    best_val = neighbor_val;
                    best_i = ni;
                    best_j = nj;
                }
            }
        }

        if (best_val >= current_val) {
            return current_val;
        }

        i = best_i;
        j = best_j;
    }
}
#endif // ALGORITHMS