#ifndef LIB_LIST_STACK
#define LIB_LIST_STACK

#include "../lib_list/list.h"

template<typename T>
class ListStack {
	List<T> _data;
public:
	ListStack() = default; // 1 test, if capacity < 0 throw
	ListStack(const ListStack& other); // 1 test


	void push(T val); //2 теста
	void pop(); //2 теста
	T top() const; //2 теста

	inline bool is_empty() const noexcept; //2 теста

	void clear() noexcept; //1 тест
};

template<typename T>
ListStack<T>::ListStack(const ListStack& other) : _data(other._data) {}

template<typename T>
void ListStack<T>::push(T val) {
	_data.push_front(val);
}

template<typename T>
void ListStack<T>::pop() {
	if (is_empty()) {
		throw std::runtime_error("Cannot be removed from an empty stack");
	}
	
	_data.pop_front();
}

template<typename T>
T ListStack<T>::top() const {
	if (is_empty()) {
		throw std::runtime_error("There are no elements");
	}

	return _data.head()->value;
}

template<typename T>
inline bool ListStack<T>::is_empty() const noexcept {
	return _data.is_empty();
}

template<typename T>
void ListStack<T>::clear() noexcept {
	while (!_data.is_empty()) {
		_data.pop_front();
	}
}

#endif  // LIB_LIST_STACK
