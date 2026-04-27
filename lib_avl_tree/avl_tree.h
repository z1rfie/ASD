#include <iostream>

template<class TKey, class TValue>
struct AVLNode {
	AVLNode<TKey, TValue> *left, *right, *parent;
	std::pair<TKey, TValue> data;
	size_t height;
};

template<class TKey, class TValue>
class AVLTree {
	AVLNode<TKey, TValue>* _root;
private:
	void left_rotate(AVLNode<TKey, TValue>* node);
	void right_rotate(AVLNode<TKey, TValue>* node);

	void RR(AVLNode<TKey, TValue>* node);
	void LL(AVLNode<TKey, TValue>* node);
	void RL(AVLNode<TKey, TValue>* node);
	void LR(AVLNode<TKey, TValue>* node);

	void recover_balance(AVLNode<TKey, TValue>* node);
	void recalculate_height(AVLNode<TKey, TValue>* node);
	int calculate_balance(AVLNode<TKey, TValue>* node);
};

template<class TKey, class TValue>
void AVLTree<TKey, TValue>::left_rotate(AVLNode<TKey, TValue>* node) {
	G				P
		\	  left(G) / \
		P->G   C        RR
		\
		C

		G				C
		\	  left(G) / \
		C->G   P        RL
		\
		P

		G				G
		/ left(P) /
		C->C       	   LR
		\ /
		P		    P

		G = node;
	P = G->right;

	G->right = nullptr;
	P->parent = G->parent;
	P->left = G;
	G->parent = P;
}

template<class TKey, class TValue>
void AVLTree<TKey, TValue>::right_rotate(AVLNode<TKey, TValue>* node) {
	G				 P
		/ right(G) / \
		P->C   G
		/
		C

		G = node;
	P = G->left;

	G->left = nullptr;
	P->parent = G->parent;
	P->right = G;
	G->parent = P;
}

template<class TKey, class TValue> G отправляем всегда деда(дед сломал баланс)
void AVLTree<TKey, TValue>::RR(AVLNode<TKey, TValue>* node) {
	G				P
		\	  left(G) / \
		P->G   C
		\
		C

		G = node;
	left_rotate(G);
}

template<class TKey, class TValue> G отправляем всегда деда(дед сломал баланс)
void AVLTree<TKey, TValue>::LL(AVLNode<TKey, TValue>* node) {
	G				 P
		/ right(G) / \
		P->C   G
		/
		C

		G = node;
	right_rotate(G);
}

template<class TKey, class TValue> G отправляем всегда деда(дед сломал баланс)
void AVLTree<TKey, TValue>::RL(AVLNode<TKey, TValue>* node) {
	G				 G						C
		\	  right(P)    \		  left(G) / \
		P->C->G   P
		/ \
		C					 P

		G = node;
	P = G->right;
	right_rotate(P);
	left_rotate(G);
}

void insert(const TKey& key, const TValue& val) { // сомнительно, надо что-то возвращать
	AVLNode<TKey, TValue>* node = BSTree::insert(key, val);
	if (node = _root) return;
	P = node->parent;
	recalculate_height(P);
	G = P->parent;
	if (!G) return;
	int balance = recalculate_balance(G);
	if (abs(balance) > 1) {
		recover_balance(G);
		return;
	}
	AVLNode<TKey, TValue>* cur = G;
	size_t prev_height;
	while (cur) {
		prev_height = cur->height;
		recalculate_height(cur);
		if (prev_height == cur->height) break;
		cur = cur->parent;
	}
}

void erase(const TKey& key) {
	AVLNode* node = BSTree::erase(key); // P для удаления
	int balance = calculate_balance(node);
	if (abs(balance)) {
		recover_balance(node);
	}
	size_t old_height = node->height;
	recalculate_height(node);
	if (old_height == node->height) break;
	node = node->parent;
}