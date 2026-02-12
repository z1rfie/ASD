#ifndef LIB_STACK
#define LIB_STACK

#include "../lib_tvector/vector.h"

template<typename T>
class Stack {
	TVector<T> _data; 
public:
	Stack(size_t size); // 1 test, if capacity < 0 throw
	Stack(const Stack& other); // 1 test

	void push(T val); //2 теста
	void pop(); //2 теста
	T top() const; //2 теста

	inline bool is_empty() const noexcept; //2 теста
	inline bool is_full() const noexcept; //2 теста

	void clear() noexcept; //1 тест
};

template<typename T>
Stack<T>::Stack(size_t size) : _data(0) {
	_data.reserve(size);
}

template<typename T>
Stack<T>::Stack(const Stack& other) : _data(other._data) {}

template<typename T>
void Stack<T>::push(T val) {
	if (is_full()) {
		throw std::runtime_error("Cannot be inserted into a filled stack");
	}
	
	_data.push_back_elem(val);
}

template<typename T>
void Stack<T>::pop() {
	if (is_empty()) {
		throw std::runtime_error("Cannot be removed from an empty stack");
	}
	
	_data.pop_back_elem();
}

template<typename T>
T Stack<T>::top() const {
	if (is_empty()) {
		throw std::runtime_error("There are no elements");
	}

	return _data.back();
}

template<typename T>
inline bool Stack<T>::is_full() const noexcept {
	return _data.is_full();
}

template<typename T>
inline bool Stack<T>::is_empty() const noexcept {
	return _data.is_empty();
}

template<typename T>
void Stack<T>::clear() noexcept {
	_data.clear();
}

#endif  // LIB_STACK
