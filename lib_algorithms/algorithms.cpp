#include "../lib_algorithms/algorithms.h"

bool check_breckets(std::string str) {
    Stack<char> stack(str.length());
    for (char c : str) {
        switch (c) {
        case '(':
            stack.push(')');
            break;
        case '{':
            stack.push('}');
            break;
        case '[':
            stack.push(']');
            break;
        case '<':
            stack.push('>');
            break;
        case ')':
        case '}':
        case ']':
        case '>':
            if (stack.is_empty() || stack.top() != c) {
                return false;
            }
            stack.pop();
            break;
        default:
            break;
        }
    }
    return stack.is_empty();
}

void read_expression(std::string expression) {
    Stack<char> stack(expression.length());
    bool expect_operand = true; // true - ожидаем операнд, false - ожидаем операцию

    for (size_t i = 0; i < expression.length(); i++) {
        char c = expression[i];

        if (std::isspace(c)) {
            continue; 
        }

        switch (c) {
        case '(':
            stack.push(')');
            expect_operand = true;
            break;
        case '{':
            stack.push('}');
            expect_operand = true;
            break;
        case '[':
            stack.push(']');
            expect_operand = true;
            break;
        case '<':
            stack.push('>');
            expect_operand = true;
            break;

        case ')':
        case '}':
        case ']':
        case '>':
            if (stack.is_empty()) {
                throw std::invalid_argument("Missing opened bracket");
            }
            if (stack.top() != c) {
                throw std::invalid_argument("Missing closed bracket");
            }
            if (expect_operand) {
                throw std::invalid_argument("Missing operand before bracket");
            }
            stack.pop();
            expect_operand = false;
            break;

        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
            if (expect_operand) {
                throw std::invalid_argument("Missing operand");
            }
            expect_operand = true;
            break;

        default:
            if (std::isalnum(c)) {
                if (!expect_operand) throw std::invalid_argument("Missing operation");
                expect_operand = false;

                while (i + 1 < expression.length() && std::isalnum(expression[i + 1])) {
                    i++;
                }
            }
            else {
                throw std::invalid_argument("Invalid character");
            }
            break;
        }
    }

    if (!stack.is_empty()) {
        throw std::invalid_argument("Missing closed bracket");
    }

    if (expect_operand) {
        throw std::invalid_argument("Missing second operand");
    }
}

int return_count_islands(const Matrix<int>& matr) {
    int n = matr.get_n();
    int m = matr.get_m();
    DSU dsu(n * m);

    int di[] = { -1, 1, 0, 0 };
    int dj[] = { 0, 0, -1, 1 };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (matr[i][j] == 1) {
                for (int k = 0; k < 4; ++k) {
                    int ni = i + di[k];
                    int nj = j + dj[k];

                    if (ni >= 0 && ni < n && nj >= 0 && nj < m &&
                        matr[ni][nj] == 1) {
                        int u = i * m + j;
                        int v = ni * m + nj;

                        dsu.func_union(u, v);
                    }
                }
            }
        }
    }

    int islands = 0;
    for (int i = 0; i < n * m; ++i) {
        if (dsu.find(i) == i && matr[i / m][i % m] == 1) {
            islands++;
        }
    }

    return islands;
}