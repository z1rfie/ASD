#ifndef LIB_LEXEM
#define LIB_LEXEM

#include <string>

enum TypeLexem { Constant, Variable, OpenBrecket, ClosedBrecket, Function, Operator };

struct Lexem {
	std::string name;
	TypeLexem type;
    double value;
	int priority;
    double (*function)(double);
    Lexem() = default;
    Lexem(std::string _name, TypeLexem _type, double _value = DBL_MAX,
        int _priority = -1, double(*_function)(double) = nullptr) :
        name(_name),
        type(_type),
        value(_value),
        priority(_priority),
        function(_function)
    {}

    std::string get_name() const { return name; }
    TypeLexem get_type() const { return type; }
    double get_value() const { return value; }
    int get_priority() const { return priority; }
    double (*get_function() const)(double) { return function; }
};

#endif  // LIB_LEXEM
