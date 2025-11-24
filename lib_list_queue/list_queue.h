#ifndef LIB_LIST_QUEUE
#define LIB_LIST_QUEUE

#include "../lib_list/list.h"

template<class T>
class ListQueue {
    List<T> _data;
public:
    ListQueue() = default;
    ListQueue(const ListQueue& other);

    void push(T val);
    void pop();
    inline T tail() const;
    inline T head() const;

    inline bool is_empty() const noexcept;

    void clear() noexcept;
};

template<class T>
ListQueue<T>::ListQueue(const ListQueue& other) : _data(other._data) {}


template<class T>
void ListQueue<T>::push(T val) {
    _data.push_back(val);
}

template<class T>
void ListQueue<T>::pop() {
    if (is_empty()) {
        throw std::runtime_error("Cannot be removed from an empty queue");
    }

    _data.pop_front();
}

template<class T>
inline T ListQueue<T>::tail() const {
    if (is_empty()) {
        throw std::runtime_error("There are no elements");
    }

    return _data.tail()->value;
}

template<class T>
inline T ListQueue<T>::head() const {
    if (is_empty()) {
        throw std::runtime_error("There are no elements");
    }

    return _data.head()->value;
}

template<class T>
inline bool ListQueue<T>::is_empty() const noexcept {
    return _data.is_empty();
}


template<class T>
void ListQueue<T>::clear() noexcept {
    while (!_data.is_empty()) {
		_data.pop_front();
	}
}

#endif  // LIB_LIST_QUEUE