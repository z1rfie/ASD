	#ifndef LIB_LIST
	#define LIB_LIST

	#include <stdexcept>

	template <class T>
	struct Node {
		T value;
		Node<T>* next;
		Node(T value_, Node<T>* next_ = nullptr) : value(value_), next(next_) {}
	};

	template <class T>
	class List {
		Node<T> *_head, *_tail;
		size_t _count;
	public:
		List();
		List(const List<T>&);
		~List();

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

			bool operator==(const Iterator& other) const {
				return _current == other._current;
			}

			Iterator& operator++() { // ++it
				_current = _current->next;  
				return *this;
			}
			Iterator operator++(int) { // it++ 
				Iterator temp = *this;
				_current = _current->next;
				return temp; 
			}

			T& operator*() const {
				return _current->value;
			}

			Node<T>* get_node() const {
				return _current;
			}
		};

		Iterator begin() { return Iterator(_head); }
		Iterator end() { return Iterator(nullptr); }

		Node<T>* head();
		Node<T>* tail();

		const Node<T>* head() const;
		const Node<T>* tail() const;
		const size_t count() const;

		bool is_empty() const;

		List& operator=(const List& other);

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
	List<T>::List() : _head(nullptr), _tail(nullptr), _count(0) {}

	template<typename T>
	List<T>::List(const List<T>& other) : _head(nullptr), _tail(nullptr), _count(0) {
		Node<T>* current = other._head;
		while (current != nullptr) {
			push_back(current->value); 
			current = current->next;
		}
	}

	template <class T>
	List<T>::~List() {
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
	Node<T>* List<T>::head() { return _head; }

	template <class T>
	Node<T>* List<T>::tail() { return _tail; }

	template <class T>
	const Node<T>* List<T>::head() const { return _head; }

	template <class T>
	const Node<T>* List<T>::tail() const { return _tail; }

	template <class T>
	const size_t  List<T>::count() const { return _count; }

	template <class T>
	bool List<T>::is_empty() const { return _head == nullptr; }

	template <class T>
	List<T>& List<T>::operator=(const List<T>& other) {
		if (this == &other)
			return *this;

		Node<T>* cur = _head;
		while (cur) {
			Node<T>* next = cur->next;
			delete cur;
			cur = next;
		}

		_head = nullptr;
		_tail = nullptr;
		_count = 0;

		Node<T>* src = other._head;
		while (src) {
			push_back(src->value);
			src = src->next;
		}

		return *this;
	}

	template <class T>
	void List<T>::push_front(const T& value) noexcept {
		Node<T>* node = new Node<T>(value, _head); 
		if (is_empty()) {
			_tail = node;
		}
		_head = node;
	
		_count++;
	}

	template <class T>
	void List<T>::push_back(const T& value) noexcept {
		Node<T>* node = new Node<T>(value, nullptr);

		if (is_empty()) {
			_head = node;
			_tail = node;
		}
		else {
			_tail->next = node;
			_tail = node;
		}

		_count++;
	}

	template <class T>
	void List<T>::insert(Node<T>* node, const T& val) { // вставляем после объекта на который указываем
		if (node == nullptr || is_empty()) throw std::invalid_argument("Node cannot be null or list is empty");

		Node<T>* new_node = new Node<T>(val, node->next);
		node->next = new_node;

		if (node == _tail) {
			_tail = new_node;
		}

		_count++;
	}

	template <class T>
	void List<T>::insert(size_t pos, const T& value) {
		if (pos > _count) throw std::out_of_range("Position out of range");
		if (pos == 0) {
			push_front(value);
			return;
		}
		if (pos == _count) {
			push_back(value);
			return;
		}

		Node<T>* cur = _head;
		for (size_t i = 0; i < pos - 1; i++) {
			cur = cur->next;
		}

		Node<T>* new_node = new Node<T>(value, cur->next);
		cur->next = new_node;
		_count++;
	}

	template <class T>
	void List<T>::pop_front() {
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
		delete cur;

		_count--;
	}

	template <class T>
	void List<T>::pop_back() {
		if (is_empty()) throw std::runtime_error("Cannot pop from empty list");

		if (_head == _tail) {
			delete _head;
			_head = nullptr;
			_tail = nullptr;
			_count = 0;
			return;
		}

		Node<T>* cur = _head;
		while (cur->next != _tail) {
			cur = cur->next;
		}

		delete _tail;
		_tail = cur;
		cur->next = nullptr;

		_count--;
	}

	template <class T>
	void List<T>::erase(size_t pos) {
		if (is_empty()) {
			throw std::runtime_error("Cannot erase from empty list");
		}
		if (pos >= _count) {
			throw std::out_of_range("Position out of range");
		}
		if (pos == 0) {
			pop_front();
			return;
		}
		if (pos == _count - 1) {
			pop_back();
			return;
		}

		Node<T>* cur = _head;
		for (size_t i = 0; i < pos - 1; i++) {
			cur = cur->next;
		}

		Node<T>* del = cur->next;
		cur->next = del->next;

		delete del;
		_count--;
	}

	template <class T>
	void List<T>::erase(Node<T>* node) {
		if (node == nullptr) throw std::invalid_argument("Node cannot be null");
		if (is_empty()) throw std::invalid_argument("List is empty");

		if (node == _head) {
			pop_front();
			return;
		}

		Node<T>* cur = _head;
		while (cur != nullptr && cur->next != node) {
			cur = cur->next;
		}

		if (cur == nullptr) throw std::invalid_argument("Node does not belong to this list");

		cur->next = node->next;
		if (node == _tail) _tail = cur;
		delete node;

		_count--;
	}

	#endif  // LIB_LIST
