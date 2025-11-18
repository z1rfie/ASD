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

//template<typename T>
//bool is_looped(List<T> list) {
//    List<T>::Iterator it1 = list.begin();
//    List<T>::Iterator it2 = list.begin();
//
//    int speed1 = 0, speed2 = 0;
//
//    while (it1 != list.end() || it2 != list.end()) {
//        it1 = ++speed1;
//        it2 = speed2 + 2;
//    }
//    
//    if (it1 == it2) {
//        return true;
//    }
//
//    return false;
//}