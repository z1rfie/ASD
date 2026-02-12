#define ALGORITHMS
#ifdef ALGORITHMS

#include "../lib_matrix/matrix.h"
#include "../lib_stack/stack.h"
#include "../lib_list/list.h"
#include "../lib_dsu/dsu.h"
#include "../lib_lexem/lexem.h"
#include <iostream>
#include <map>

bool check_breckets(std::string str);

void read_expression(std::string expression);

template<typename T>
bool is_looped(List<T>& list) {
    List<T>::Iterator slow = list.begin();
    List<T>::Iterator fast = list.begin();

    if (slow == list.end()) {
        return false;
    }

    while (fast != list.end()) {
        ++slow;

        ++fast; 
        if (fast == list.end()) break;
        ++fast;

        if (slow == fast) {
            return true;
        }
    }
    return false;
}

template<typename T>
bool is_looped_reversal_signs(List<T>& list) {
    Node<T>* cur = list.head();
    Node<T>* prev = nullptr;
    Node<T>* next = nullptr;
    Node<T>* start = list.head();

    while (cur != nullptr) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
        if (cur == start) {
            return true;
        }
    }
    return false;
}

template<typename T>
Node<T>* find_loop(List<T>& list) {
    auto slow = list.begin();
    auto fast = list.begin();

    if (slow == list.end()) {
        return nullptr;
    }

    bool has_loop = false;

    while (fast != list.end()) {
        ++slow;

        ++fast; 
        if (fast == list.end()) break;
        ++fast;

        if (slow == fast) {
            has_loop = true;
            break;
        }
    }

    if (!has_loop) {
        return nullptr;
    }

    slow = list.begin();

    while (slow != fast) {
        ++slow;
        ++fast;
    }

    return slow.get_node();
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

int return_count_islands(const Matrix<int>& matr);

List<Lexem> build_polish(List<Lexem>& lexems);

double calculate_polish(List<Lexem>& polish_record, std::map<std::string, double>& variables);

Matrix<bool> make_labirint(int X, int Y, int N, int M);

void print(Matrix<bool> labirint, int N, int M);

#endif // ALGORITHMS