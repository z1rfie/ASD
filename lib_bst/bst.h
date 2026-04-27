#include <iostream>

template <class TKey, class TValue>
struct Node {
	std::pair<TKey, TValue> data;
	Node<TKey, TValue>* left;
	Node<TKey, TValue>* right;

	Node(const TKey& key, const TValue& val)
		: data(key, val), left(nullptr), right(nullptr) {
	}
};

template <class TKey, class TValue>
class BSTree {
	Node<TKey, TValue>* _root;
public:
	BSTree();
	~BSTree();

	void insert(const TKey& key, const TValue& value);
	void erase(const TKey& key);
	TValue* find(const TKey& key) const noexcept;
	bool is_empty() const noexcept;

	void clear() noexcept;
	void print_table(std::ostream& os) const noexcept;
	void print_DLCR() const noexcept;
private:
	Node<TKey, TValue>* find_parent(const TKey& key) const noexcept;
	void clear_rec(Node<TKey, TValue>*) noexcept;
	void print_table_rec(Node<TKey, TValue>* node, std::ostream& os) const noexcept;
	void print_DLCR_rec(Node<TKey, TValue>*) const noexcept;
};

template <class TKey, class TValue>
BSTree<TKey, TValue>::BSTree() : _root(nullptr) {}

template <class TKey, class TValue>
BSTree<TKey, TValue>::~BSTree() { clear(); }

template <class TKey, class TValue>
void BSTree<TKey, TValue>::insert(const TKey& key, const TValue& val) {
	Node<TKey, TValue>* parent = find_parent(key);
	if (!parent) {
		_root = new Node<TKey, TValue>(key, val);
		return;
	}
	if (parent->data.first < key && !parent->right) {
		parent->right = new Node<TKey, TValue>(key, val);
		return;
	}
	if (parent->data.first > key && !parent->left) {
		parent->left = new Node<TKey, TValue>(key, val);
		return;
	}
	throw std::logic_error("The key is already occupied");
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::erase(const TKey& key) {
	Node<TKey, TValue>* parent = find_parent(key);

	Node<TKey, TValue>* node = nullptr;
	Node<TKey, TValue>* real_parent = nullptr;

	if (_root && _root->data.first == key) {
		node = _root;
		real_parent = nullptr;
	}
	else if (parent && parent->right && parent->right->data.first == key) {
		node = parent->right;
		real_parent = parent;
	}
	else if (parent && parent->left && parent->left->data.first == key) {
		node = parent->left;
		real_parent = parent;
	}

	if (!node) return;

	if (!node->left && !node->right) {
		if (!real_parent) _root = nullptr;
		else if (real_parent->right == node) real_parent->right = nullptr;
		else real_parent->left = nullptr;
		delete node;
	}
	else if (!node->left) {
		if (!real_parent) _root = node->right;
		else if (real_parent->right == node) real_parent->right = node->right;
		else real_parent->left = node->right;
		delete node;
	}
	else if (!node->right) {
		if (!real_parent) _root = node->left;
		else if (real_parent->right == node) real_parent->right = node->left;
		else real_parent->left = node->left;
		delete node;
	}
	else {
		Node<TKey, TValue>* pred_parent = node;
		Node<TKey, TValue>* pred = node->left;
		while (pred->right) {
			pred_parent = pred;
			pred = pred->right;
		}
		node->data = pred->data;
		if (pred_parent == node) pred_parent->left = pred->left;
		else pred_parent->right = pred->left;
		delete pred;
	}
}

template <class TKey, class TValue>
Node<TKey, TValue>* BSTree<TKey, TValue>::find_parent(const TKey& key) const noexcept {
	if (is_empty()) return nullptr;

	if (_root->data.first == key) return _root;

	Node<TKey, TValue>* cur = _root;
	while (1) {
		if (cur->data.first > key) {
			if (!cur->left) return cur;

			if (cur->left->data.first == key) return cur;
			else cur = cur->left;
		}
		else {
			if (!cur->right) return cur;

			if (cur->right->data.first == key) return cur;
			else cur = cur->right;
		}
	}
}

template <class TKey, class TValue>
TValue* BSTree<TKey, TValue>::find(const TKey& key) const noexcept {
	Node<TKey, TValue>* parent = find_parent(key);
	if (!parent) return nullptr;

	if (parent->data.first == key) return &parent->data.second;
	if (parent->left && parent->left->data.first == key) return &parent->left->data.second;
	if (parent->right && parent->right->data.first == key) return &parent->right->data.second;
	return nullptr;
}

template <class TKey, class TValue>
bool BSTree<TKey, TValue>::is_empty() const noexcept {
	return _root == nullptr;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::clear() noexcept {
	clear_rec(_root);
	_root = nullptr;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::clear_rec(Node<TKey, TValue>* node) noexcept {
	if (!node) return;
	clear_rec(node->left);
	clear_rec(node->right);
	delete node;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::print_DLCR() const noexcept {
	print_DLCR_rec(_root);
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::print_DLCR_rec(Node<TKey, TValue>* node) const noexcept {
	if (!node) return;
	print_DLCR_rec(node->left);
	std::cout << node->data.first << " ";
	print_DLCR_rec(node->right);
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::print_table(std::ostream& os) const noexcept {
	print_table_rec(_root, os);
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::print_table_rec(Node<TKey, TValue>* node, std::ostream& os) const noexcept {
	if (!node) return;
	print_table_rec(node->left, os);
	os << "| " << node->data.first << " | " << node->data.second << " |" << std::endl;
	print_table_rec(node->right, os);
}