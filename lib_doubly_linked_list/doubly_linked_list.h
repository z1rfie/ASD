#ifndef LIB_DOUBLY_LINKED_LIST
#define LIB_DOUBLY_LINKED_LIST

#include <stdexcept>

template <class T>
struct Node {
	T value;
	Node<T>* next;
	Node<T>* prev;
	Node(T value_, Node<T>* next_ = nullptr, Node<T>* prev_ = nullptr) : value(value_), next(next_), prev(prev_) {}
};

template <class T>
class DoublyLinkedList {
	Node<T> *_head, *_tail;
	size_t _count;
public:
	DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList&);
	~DoublyLinkedList();

	class Iterator {
		Node<T>* _current;
	public:
		Iterator() : _current(nullptr) {}
		Iterator(Node<T>* node) : _current(node) {}

		Iterator& operator=(const Iterator& other) {
			_current = other._current;
			return *this;
		}

		bool operator!=(const Iterator& other) const {
			return _current != other._current;
		}

		Iterator& operator++() {
			_current = _current->next;
			return *this;
		}
		Iterator operator++(int) { 
			Iterator temp = *this;
			_current = _current->next;
			return temp;
		}

		Iterator operator--() {
			_current = _current->prev;
			return *this;
		}

		Iterator operator--(int) {
			Iterator temp = *this;
			_current = _current->prev;
			return temp;
		}

		T& operator*() const {
			return _current->value;
		}
	};

	Iterator begin() const { return Iterator(_head); }
	Iterator end() const { return Iterator(nullptr); }

	Node<T>* head() const;
	Node<T>* tail() const;
	size_t count() const;

	bool is_empty() const;

	// вставка
	void push_front(const T& value) noexcept;
	void push_back(const T& value) noexcept;
	void insert(size_t pos, const T& value);
	void insert(Node<T>* node, const T& value);

	// удаление 
	void pop_front();
	void pop_back();
	void erase(size_t pos);
	void erase(Node<T>* node);	
};

template <class T>
DoublyLinkedList<T>::DoublyLinkedList() : _head(nullptr), _tail(nullptr), _count(0) {}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other) : _head(nullptr), _tail(nullptr), _count(0) {
	for (auto it = other.begin(); it != other.end(); ++it) {
		push_back(*it);
	}
}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	Node<T>* current = _head;
	while (current != nullptr) {
		Node<T>* next = current->next;
		delete current;
		current = next;
	}
	_head = nullptr;
	_tail = nullptr;
	_count = 0;
}

template <class T>
Node<T>* DoublyLinkedList<T>::head() const { return _head; }

template <class T>
Node<T>* DoublyLinkedList<T>::tail() const { return _tail; }

template <class T>
size_t  DoublyLinkedList<T>::count() const { return _count; }

template <class T>
bool DoublyLinkedList<T>::is_empty() const { return _count == 0; }

template <class T>
void DoublyLinkedList<T>::push_front(const T& value) noexcept {
	Node<T>* node = new Node<T>(value, _head);

	if (is_empty()) {
		_tail = node;
	}
	else {
		_head->prev = node; 
	}

	_head = node;
	_count++;
}

template <class T>
void DoublyLinkedList<T>::push_back(const T& value) noexcept {
	Node<T>* node = new Node<T>(value);

	if (is_empty()) {
		_head = node;
		_tail = node;
	}
	else {
		node->prev = _tail;
		_tail->next = node;
		_tail = node;
	}

	_count++;
}

template <class T>
void DoublyLinkedList<T>::insert(Node<T>* node, const T& val) {
	if (node == nullptr) throw std::invalid_argument("Node cannot be null");
	if (is_empty()) throw std::invalid_argument("List is empty");

	Node<T>* new_node = new Node<T>(val, node->next, node);
	node->next = new_node;

	if (new_node->next != nullptr) new_node->next->prev = new_node;
	if (node == _tail) _tail = new_node;

	_count++;
}

template <class T>
void DoublyLinkedList<T>::insert(size_t pos, const T& value) {
	if (pos > _count) throw std::out_of_range("Position out of range");
	if (pos == 0) {
		push_front(value);
		return;
	}
	if (pos == _count) {
		push_back(value);
		return;
	}

	Node<T>* prev_node = _head;
    for (size_t i = 0; i < pos - 1; i++) {
        prev_node = prev_node->next;
    }
    
	insert(prev_node, value);
}

template <class T>
void DoublyLinkedList<T>::pop_front() {
	if (is_empty()) throw std::runtime_error("Cannot pop from empty list");

	if (_head == _tail) {
		delete _head;
		_head = nullptr;
		_tail = nullptr;
		_count = 0;
		return;
	}

	Node<T>* cur = _head;
	_head = _head->next;
	_head->prev = nullptr;
	delete cur;

	_count--;
}

template <class T>
void DoublyLinkedList<T>::pop_back() {
	if (is_empty()) throw std::runtime_error("Cannot pop from empty list");

	if (_head == _tail) {
		delete _head;
		_head = nullptr;
		_tail = nullptr;
		_count = 0;
		return;
	}

	Node<T>* cur = _tail;
	_tail = _tail->prev;
	_tail->next = nullptr;
	delete cur;

	_count--;
}

template <class T>
void DoublyLinkedList<T>::erase(Node<T>* node) {
	if (node == nullptr) throw std::invalid_argument("Node cannot be null");
	if (is_empty()) throw std::invalid_argument("List is empty");

	if (node == _head) {
		pop_front();
		return;
	}

	if (node == _tail) {
		pop_back();
		return;
	}

	node->prev->next = node->next;
	node->next->prev = node->prev;

	delete node;
	_count--;
}

template <class T>
void DoublyLinkedList<T>::erase(size_t pos) {
	if (is_empty()) {
		throw std::runtime_error("Cannot erase from empty list");
	}

	if (pos > _count) {
		throw std::out_of_range("Position out of range");
	}
	if (pos == 1) {
		pop_front();
		return;
	}
	if (pos == _count) {
		pop_back();
		return;
	}

	Node<T>* cur = _head;
	for (size_t i = 0; i < pos - 1; i++) {
		cur = cur->next;
	}

	erase(cur);
}

#endif  // LIB_DOUBLY_LINKED_LIST
