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
                throw std::invalid_argument("Отсутствует открытая скобка");
            }
            if (stack.top() != c) {
                throw std::invalid_argument("Отсутствует закрытая скобка");
            }
            if (expect_operand) {
                throw std::invalid_argument("Пропущенный операнд перед скобкой");
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
                throw std::invalid_argument("Отсутствующий операнд");
            }
            expect_operand = true;
            break;

        default:
            if (std::isalnum(c)) {
                if (!expect_operand) throw std::invalid_argument("Пропущенная операция");
                expect_operand = false;

                while (i + 1 < expression.length() && std::isalnum(expression[i + 1])) {
                    i++;
                }
            }
            else {
                throw std::invalid_argument("Недопустимый символ");
            }
            break;
        }
    }

    if (!stack.is_empty()) {
        throw std::invalid_argument("Отсутствует закрытая скобка");
    }

    if (expect_operand) {
        throw std::invalid_argument("Пропущенный второй операнд");
    }
}


int return_count_islands(const Matrix<int>& matr) {
    int n = matr.get_n();
    int m = matr.get_m();
    DSU dsu(n * m);

    int di[] = { -1, 1, 0, 0 };
    int dj[] = { 0, 0, -1, 1 };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matr[i][j] == 1) {
                for (int k = 0; k < 4; k++) {
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
    for (int i = 0; i < n * m; i++) {
        if (dsu.find(i) == i && matr[i / m][i % m] == 1) {
            islands++;
        }
    }

    return islands;
}

List<Lexem> build_polish(List<Lexem>& lexems) {
    List<Lexem> postfix_form;
    Stack<Lexem> stack(50);

    Node<Lexem>* current = lexems.head();

    while (current != nullptr) {
        Lexem lexem = current->value;

        switch (lexem.get_type()) {
        case Constant:
        case Variable:
            postfix_form.push_back(lexem);
            break;

        case OpenBrecket:
            stack.push(lexem);
            break;

        case ClosedBrecket:
            while (!stack.is_empty() && stack.top().get_type() != OpenBrecket) {
                postfix_form.push_back(stack.top()); stack.pop();
            }

            if (!stack.is_empty() && stack.top().get_type() == OpenBrecket) {
                stack.pop();
            }

            if (!stack.is_empty() && stack.top().get_type() == Function) {
                postfix_form.push_back(stack.top()); stack.pop();
            }
            break;

        case Function:
            stack.push(lexem);
            break;

        case Operator:
            while (!stack.is_empty() && (stack.top().get_type() == Operator || stack.top().get_type() == Function)
                && stack.top().get_priority() >= lexem.get_priority()) {
                postfix_form.push_back(stack.top());
                stack.pop();
            }
            stack.push(lexem);
            break;

        default:
            break;
        }

        current = current->next;
    }

    while (!stack.is_empty()) {
        postfix_form.push_back(stack.top());
        stack.pop();
    }

    return postfix_form;
}

double calculate_polish(List<Lexem>& polish_record, std::map<std::string, double>& variables) {
    Stack<double> stack(50);

    Node<Lexem>* current = polish_record.head();

    while (current != nullptr) {
        Lexem lexem = current->value;

        switch (lexem.get_type()) {
        case Constant: {
            stack.push(lexem.get_value());
            break;
        }
        case Variable: {
            stack.push(variables[lexem.get_name()]);
            break;
        }
        case Operator: {
            double right = stack.top(); stack.pop();
            double left = stack.top(); stack.pop();

            if (lexem.get_name() == "+") stack.push(left + right);
            else if (lexem.get_name() == "-") stack.push(left - right);
            else if (lexem.get_name() == "*") stack.push(left * right);
            else if (lexem.get_name() == "/") stack.push(left / right);
            else if (lexem.get_name() == "^") stack.push(pow(left, right));
            break;
        }
        case Function: {
            double arg = stack.top(); stack.pop();
            stack.push(lexem.get_function()(arg));
            break;
        }
        default:
            break;
        }
        current = current->next;
    }
    return stack.top();
}

Matrix<bool> make_labirint(int X, int Y, int N, int M) {
    if (M <= 0 || N <= 0) {
        throw std::out_of_range("Нельзя создать такой лабиринт");
    }

    if (X < 0 || X > M || Y < 0 || Y > M) {
        throw std::out_of_range("Недопустимое значение");
    }

    srand(time(NULL));

    Matrix<bool> matr(N, M);
    DSU dsu(N * M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matr[i][j] = true;
        }
    }

    matr[0][X] = false;
    matr[N - 1][Y] = false;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int cell_1 = i * M + j;
            if (j + 1 < M) {
                int cell_2 = i * M + (j + 1);
                if (dsu.find(cell_1) != dsu.find(cell_2)) {
                    if (rand() % 2) {
                        dsu.func_union(cell_1, cell_2);
                        matr[i][j + 1] = false;
                        matr[i][j] = false;
                    }
                }
            }

            if (i + 1 < N) {
                int cell_2 = (i + 1) * M + j;
                if (dsu.find(cell_1) != dsu.find(cell_2)) {
                    if (rand() % 2) {
                        dsu.func_union(cell_1, cell_2);
                        matr[i + 1][j] = false;
                        matr[i][j] = false;
                    }
                }
            }
        }
    }

    return matr;
}

void print(Matrix<bool>& labirint, int N, int M) {
    for (int j = 0; j < M; j++) {
        std::cout << " __";
    }
    std::cout << std::endl;

    for (int i = 0; i < N; i++) {
        std::cout << "|";

        for (int j = 0; j < M; j++) {
            if (!labirint[i][j]) { 
                std::cout << "  ";
            }
            else { 
                std::cout << "__";
            }

            if (j == M - 1) {
                std::cout << "|"; 
            }
            else {
                if (labirint[i][j + 1] && labirint[i][j]) {
                    std::cout << "|"; 
                }
                else {
                    std::cout << " "; 
                }
            }
        }
        std::cout << std::endl;
    }
}