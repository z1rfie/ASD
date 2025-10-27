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
    for (char c : expression) {
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
            if (stack.is_empty()) {
                throw std::invalid_argument("Missing opened brecket");
            }
            if (stack.top() != c) {
                throw std::invalid_argument("Missing closed brecket");
            }
            stack.pop();
            break;
        default:
            break;
        }
        if (!stack.is_empty()) {
            throw std::invalid_argument("Missing opening brackets");
        }

    }
}