#include <iostream>
#include "../lib_list_queue/list_queue.h"

template <class TKey, class TValue>
struct NodeTree {
	std::pair<TKey, TValue> data;
	NodeTree *left, *right;

	NodeTree(const TKey& key, const TValue& val)
		: data(key, val), left(nullptr), right(nullptr) {}
};

template <class TKey, class TValue>
class Tree {
	NodeTree<TKey, TValue>* _root;
public:
	Tree();
	~Tree();

	void insert(const TKey&, const TValue&);
	TValue* find(const TKey&) const noexcept; 
	void erase(const TKey&);
	bool is_empty() const noexcept;
	void clear() noexcept; 
	
	void print_w() const noexcept;
	void print_DLCR() const noexcept;
	void print_DLRC() const noexcept;
	void print_DCLR() const noexcept;
private:
	void clear_rec(NodeTree<TKey, TValue>*) noexcept;
	void print_DLCR_rec(NodeTree<TKey, TValue>*) const noexcept;
	void print_DLRC_rec(NodeTree<TKey, TValue>*) const noexcept;
	void print_DCLR_rec(NodeTree<TKey, TValue>*) const noexcept;
};

template <class TKey, class TValue>
Tree<TKey, TValue>::Tree() : _root(nullptr) {}

template <class TKey, class TValue>
Tree<TKey, TValue>::~Tree() { clear(); }

template <class TKey, class TValue>
void Tree<TKey, TValue>::insert(const TKey & key, const TValue & val) {
	NodeTree<TKey, TValue>* node = new NodeTree<TKey, TValue>(key, val);
	if (is_empty()) { _root = node; return; }
	NodeTree<TKey, TValue>* cur = nullptr;
	ListQueue<NodeTree<TKey, TValue>*> q; q.push(_root);

	while (1) {
		cur = q.head(); q.pop();
		if (!cur->left) { cur->left = node; return; }
		if (!cur->right) { cur->right = node; return; }
		q.push(cur->left);
		q.push(cur->right);
	}
}

template <class TKey, class TValue>
TValue* Tree<TKey, TValue>::find(const TKey& key) const noexcept {
	if (is_empty()) return nullptr;
	ListQueue<NodeTree<TKey, TValue>*> q;
	q.push(_root);
	while (!q.is_empty()) {
		NodeTree<TKey, TValue>* cur = q.head(); q.pop();
		if (cur->data.first == key) return &cur->data.second;
		if (cur->left)  q.push(cur->left);
		if (cur->right) q.push(cur->right);
	}
	return nullptr;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::erase(const TKey& key) {
	if (is_empty()) return;

	NodeTree<TKey, TValue>* node_to_delete = nullptr;
	NodeTree<TKey, TValue>* last_parent = nullptr;
	NodeTree<TKey, TValue>* last = _root;

	ListQueue<NodeTree<TKey, TValue>*> q;
	q.push(_root);
	while (!q.is_empty()) {
		NodeTree<TKey, TValue>* cur = q.head(); q.pop();
		if (cur->data.first == key) node_to_delete = cur;
		if (cur->left) { last_parent = cur; last = cur->left;  q.push(cur->left); }
		if (cur->right) { last_parent = cur; last = cur->right; q.push(cur->right); }
	}

	if (!node_to_delete) return;

	if (node_to_delete != last) node_to_delete->data = last->data;

	if (!last_parent) { delete _root; _root = nullptr; }
	else if (last_parent->right == last) {
		delete last_parent->right; last_parent->right = nullptr;
	}
	else {
		delete last_parent->left;  last_parent->left = nullptr;
	}
}

template <class TKey, class TValue>
bool Tree<TKey, TValue>::is_empty() const noexcept { return _root == nullptr; }

template <class TKey, class TValue>
void Tree<TKey, TValue>::clear() noexcept {
	clear_rec(_root);
	_root = nullptr;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::clear_rec(NodeTree<TKey, TValue>* node) noexcept {
	if (!node) return;
	clear_rec(node->left);
	clear_rec(node->right);
	delete node;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_w() const noexcept {
	if (is_empty()) return;
	ListQueue<NodeTree<TKey, TValue>*> q;
	NodeTree<TKey, TValue>* cur = nullptr;
	q.push(_root);
	while (!q.is_empty()) {
		cur = q.head();
		std::cout << cur->data.first << " ";
		q.pop();
		if (cur->left) {
			q.push(cur->left);
		}
		if (cur->right) {
			q.push(cur->right);
		}
	}
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_DLRC() const noexcept {
	print_DLRC_rec(_root);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_DLRC_rec(NodeTree<TKey, TValue>* node) const noexcept {
	if (node == nullptr) return;
	print_DLRC_rec(node->left);
	print_DLRC_rec(node->right);
	std::cout << node->data.first << " ";
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_DCLR() const noexcept {
	print_DCLR_rec(_root);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_DCLR_rec(NodeTree<TKey, TValue>* node) const noexcept {
	if (node == nullptr) return;
	std::cout << node->data.first << " "; 
	print_DCLR_rec(node->left);
	print_DCLR_rec(node->right);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_DLCR() const noexcept {
	print_DLCR_rec(_root);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_DLCR_rec(NodeTree<TKey, TValue>* node) const noexcept {
	if (node == nullptr) return;
	print_DLCR_rec(node->left);
	std::cout << node->data.first << " ";
	print_DLCR_rec(node->right);
}
