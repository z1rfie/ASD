#ifndef LIB_PARSER
#define LIB_PARSER

#include "../lib_list/list.h"
#include "../lib_lexem/lexem.h"
#include <sstream>
#include <iostream>
#include <string>

double factorial(int n) {
    double res = 1;
    for (int i = 1; i <= n; i++) res *= i;
    return res;
}

double sum_of_sin(double x) {
    double res = 0;
    double sign = 1;

    for (int i = 1; i <= 9; i += 2) {
        double term = pow(x, i) / factorial(i);
        res += sign * term;
        sign = -sign;
    }
    return res;
}

double sum_of_cos(double x) {
    double res = 1;
    double sign = -1;

    for (int i = 2; i <= 8; i += 2) {
        double term = pow(x, i) / factorial(i);
        res += sign * term;
        sign = -sign;
    }
    return res;
}

double sum_of_tg(double x) {
    double sin = sum_of_sin(x);
    double cos = sum_of_cos(x);

    if (cos == 0) throw std::runtime_error("tg undefined (cos near 0)");

    return sin / cos;
}

double my_abs(double x) {
    return (x < 0) ? -x : x;
}

namespace Parser {
    int get_priority(char op) {
        if (op == '^') return 3;
        if (op == '*' || op == '/') return 2;
        if (op == '+' || op == '-') return 1;
        return 0;
    }

    double (*get_function_ptr(const std::string& name))(double) {
        if (name == "sin") return sum_of_sin;
        if (name == "cos") return sum_of_cos;
        if (name == "tg")  return sum_of_tg;
        if (name == "abs") return my_abs;
        return nullptr;
    }

    std::invalid_argument parse_error(const std::string& expr, int pos, const std::string& description) {
        std::string msg;

        msg += "Input expression: " + expr + "\n";
        msg += "                  ";
        msg += std::string(pos, ' ') + "^\n";
        msg += "Error in function 'Parser::parse()' at ";
        msg += std::to_string(pos + 1);
        msg += " symbol: " + description;

        return std::invalid_argument(msg);
    }

    List<Lexem> parse(const std::string& expr) {
        List<Lexem> lexems;
        bool expect_operand = true;
        bool abs_opened = false;
        int brackets = 0;

        for (int i = 0; i < expr.length(); i++) {
            char c = expr[i];

            if (isspace(c)) continue;

            if (isdigit(c)) {
                if (!expect_operand) throw parse_error(expr, i, "Unexpected number");

                std::string num_str;
                while (i < expr.length() && isdigit(expr[i])) {
                    num_str += expr[i++];
                }
                i--;

                lexems.push_back(Lexem(num_str, Constant, std::stoi(num_str)));
                expect_operand = false;
            }

            else if (isalpha(c) || c == '_') {
                if (!expect_operand) throw parse_error(expr, i, "Unexpected identifier");

                int pos = i;
                std::string name;
                while (i < expr.length() && (isalnum(expr[i]) || expr[i] == '_')) {
                    name += expr[i++];
                }

                if (i < expr.length() && expr[i] == '(') {
                    double (*f)(double) = get_function_ptr(name);

                    if (f == nullptr) {
                        throw parse_error(expr, pos, "Unknown function: " + name);
                    }

                    lexems.push_back(Lexem(name, Function, 0, 4, f));
                    i--; 
                }
                else {
                    lexems.push_back(Lexem(name, Variable));
                    expect_operand = false;
                    i--;
                }
            }

            else if (std::string("+-*/^").find(c) != std::string::npos) {
                if (expect_operand) {
                    if (c == '-') {
                        lexems.push_back(Lexem("0", Constant, 0));
                    }
                    else {
                        throw parse_error(expr, i, "Operator without operand");
                    }
                }
                lexems.push_back(Lexem(std::string(1, c), Operator, 0, get_priority(c)));
                expect_operand = true;
            }

            else if (c == '|') {
                if (!abs_opened) {
                    lexems.push_back(Lexem("abs", Function, 0, 4, my_abs));
                    lexems.push_back(Lexem("(", OpenBrecket));

                    abs_opened = true;
                    brackets++;
                    expect_operand = true;
                }
                else {
                    lexems.push_back(Lexem(")", ClosedBrecket));

                    abs_opened = false;
                    brackets--;
                    expect_operand = false; 
                }
            }

            else if (c == '(' || c == '{' || c == '[') {
                brackets++;
                lexems.push_back(Lexem(std::string(1, c), OpenBrecket));
                expect_operand = true;
            }
            else if (c == ')' || c == '}' || c == ']') {
                if (--brackets < 0) throw parse_error(expr, i, "Closing bracket without opening");
                if (expect_operand) throw parse_error(expr, i, "Empty expression or operator before bracket");

                lexems.push_back(Lexem(std::string(1, c), ClosedBrecket));
                expect_operand = false;
            }
            else {
                throw parse_error(expr, i, "Unknown character");
            }
        }

        if (brackets != 0) throw std::invalid_argument("Brackets balance error");
        return lexems;
    }
}

#endif