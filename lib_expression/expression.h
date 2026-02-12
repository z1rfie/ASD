#ifndef LIB_EXPRESSION
#define LIB_EXPRESSION

#include <map>
#include "../lib_list/list.h"
#include "../lib_lexem/lexem.h"
#include "../lib_parser/parser.h"
#include "../lib_algorithms/algorithms.h"

class Expression { 
	int id;
	std::string expression;
	List<Lexem> lexems;
	List<Lexem> polish_record;
	std::map<std::string, double> variables;
public:
	Expression() = default;
	Expression(int _id, const std::string& _expression);
	Expression(int _id, const List<Lexem>& _lexems);

	void set_variables();
	int calculate();

	int get_id() const;
	std::string get_expression() const;
	const List<Lexem>& get_lexems() const;
	const List<Lexem>& get_polish_record() const;
	const std::map<std::string, double>& get_variables() const;
};

Expression::Expression(int _id, const std::string& _expression) : id(_id), expression(_expression) {
	lexems = Parser::parse(expression);
	polish_record = build_polish(lexems);
}

Expression::Expression(int _id, const List<Lexem>& _lexems) : id(_id), lexems(_lexems) {
	polish_record = build_polish(lexems);
}

void Expression::set_variables() {
	Node<Lexem>* current = lexems.head();

	while (current != nullptr) {
		if (current->value.get_type() == Variable) {
			std::string name = current->value.get_name();
			if (variables.find(name) == variables.end()) {
				double val;
				std::cout << "¬ведите значение дл€ " << name << ": ";
				std::cin >> val;
				variables[name] = val;
			}
		}
		current = current->next;
	}
}

int Expression::calculate() {
	return calculate_polish(polish_record, variables);
}

int Expression::get_id() const { return id; }
std::string Expression::get_expression() const { return expression; }
const List<Lexem>& Expression::get_lexems() const { return lexems; }
const List<Lexem>& Expression::get_polish_record() const { return polish_record; }
const std::map<std::string, double>& Expression::get_variables() const { return variables; }

#endif  // LIB_EXPRESSION
