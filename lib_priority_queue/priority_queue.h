#ifndef LIB_PRIORITY_QUEUE
#define LIB_PRIORITY_QUEUE

#include "../lib_heap/heap.h"

template<typename T>
struct PriorityElement {
    T _value;
    int _priority;
    int _serial_number;

    bool operator>(const PriorityElement& other) const {
        if (_priority == other._priority) {
            return _serial_number < other._serial_number;
        }
        return _priority < other._priority;
    }
    bool operator<(const PriorityElement& other) const {
        if (_priority == other._priority) {
            return _serial_number > other._serial_number;
        }
        return _priority > other._priority;
    }
};

template<typename T>
class PriorityQueue {
    Heap<PriorityElement<T>> heap;
    int last_number = 1;
public:
    PriorityQueue();

    void push(const T& value, int priority);
    T pop();
    T& front();

    bool is_empty() const;
    int size() const;

    void print();
};

template<typename T>
PriorityQueue<T>::PriorityQueue() {}

template<typename T>
void PriorityQueue<T>::push(const T& value, int priority) {
    PriorityElement<T> elem;
    elem._value = value;
    elem._priority = priority;
    elem._serial_number = last_number++;

    heap.push(elem);
}

template<typename T>
T PriorityQueue<T>::pop() {
    return heap.pop()._value;
}

template<typename T>
T& PriorityQueue<T>::front() {
    return heap.top()._value;
}

template<typename T>
bool PriorityQueue<T>::is_empty() const {
    return heap.is_empty();
}

template<typename T>
int PriorityQueue<T>::size() const {
    return heap.size();
}

template<typename T>
void PriorityQueue<T>::print() {
    heap.print();
}

#endif  // LIB_PRIORITY_QUEUE