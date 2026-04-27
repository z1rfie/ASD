#ifndef LIB_HEAP
#define LIB_HEAP

#pragma once
#include "../lib_tvector/vector.h"

template<typename T>
class Heap {
    TVector<T> heap;
public:
    Heap();

    void push(const T& value);
    T pop();
    T& top();

    bool is_empty() const;
    int size() const;

    void print();
private:
    void sift_up(int i);
    void sift_down(int i);
};

template<typename T>
Heap<T>::Heap() {}

template<typename T>
void Heap<T>::push(const T& value) {
    heap.push_back_elem(value);
    sift_up(heap.size() - 1);
}

template<typename T>
T Heap<T>::pop() {
    if (heap.is_empty())
        throw std::runtime_error("Heap is empty");

    T root = heap[0];

    heap[0] = heap[heap.size() - 1];
    heap.pop_back_elem();

    if (!heap.is_empty())
        sift_down(0);

    return root;
}

template<typename T>
T& Heap<T>::top() {
    if (heap.is_empty())
        throw std::runtime_error("Heap is empty");
    return heap[0];
}

template<typename T>
bool Heap<T>::is_empty() const {
    return heap.is_empty();
}

template<typename T>
int Heap<T>::size() const {
    return heap.size();
}

template<typename T>
void Heap<T>::print() {
    heap.print_elems();
}

template<typename T>
void Heap<T>::sift_up(int i) {
    while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

template<typename T>
void Heap<T>::sift_down(int i) {
    int n = heap.size();

    while (2 * i + 1 < n) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (heap[left] < heap[smallest])
            smallest = left;

        if (right < n && heap[right] < heap[smallest])
            smallest = right;

        if (smallest == i)
            break;

        swap(&heap[i], &heap[smallest]);
        i = smallest;
    }
}

#endif  // LIB_HEAP
