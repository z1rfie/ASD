#ifndef LIB_QUEUE
#define LIB_QUEUE

template<class T>
class Queue {
    T* _data;
    size_t _size;
    size_t _head;
    size_t _tail;
    size_t _count;
public:
    Queue(size_t size);
    Queue(const Queue& other);
    ~Queue();

    void push(T val);
    void pop();
    inline T tail() const;
    inline T head() const;

    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;

    void clear() noexcept;
};

template<class T>
Queue<T>::Queue(size_t size) : _size(size), _head(0), _tail(0), _count(0) {
    _data = new T[_size];
}

template<class T>
Queue<T>::Queue(const Queue& other) : _size(other._size), _head(other._head), _tail(other._tail), _count(other._count) {
    _data = new T[_size];
    for (int i = 0; i < _size; i++) {
        _data[i] = other._data[i];
    }
}

template<class T>
Queue<T>::~Queue() {
    delete[] _data;
}

template<class T>
void Queue<T>::push(T val) {
    if (is_full()) {
        throw std::runtime_error("Cannot be inserted into a filled queue");
    }

    _data[_tail] = val;
    _tail = (_tail + 1) % _size;
    _count++;
}

template<class T>
void Queue<T>::pop() {
    if (is_empty()) {
        throw std::runtime_error("Cannot be removed from an empty queue");
    }

    _head = (_head + 1) % _size;
    _count--;
}

template<class T>
inline T Queue<T>::tail() const {
    if (is_empty()) {
        throw std::runtime_error("There are no elements");
    }

    return _data[(_tail - 1 + _size) % _size];
}

template<class T>
inline T Queue<T>::head() const {
    if (is_empty()) {
        throw std::runtime_error("There are no elements");
    }

    return _data[_head];
}

template<class T>
inline bool Queue<T>::is_empty() const noexcept {
    return _count == 0;
}

template<class T>
inline bool Queue<T>::is_full() const noexcept {
    return _count == _size;
}

template<class T>
void Queue<T>::clear() noexcept {
    _head = 0;
    _tail = 0;
    _count = 0;
}

#endif  // LIB_QUEUE