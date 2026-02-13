#include "dsu.h"

const int* DSU::parent() const {
	return _parent;
}

int* DSU::parent() {
	return _parent;
}

const int* DSU::rank() const {
	return _rank;
}

const size_t DSU::size() const {
	return _size;
}

DSU::DSU(size_t size) : _size(size) {
	_parent = new int[size];
	_rank = new int[size];

	for (size_t i = 0; i < size; i++) {
		_parent[i] = i;
		_rank[i] = 0;
	}
}

DSU::DSU(const DSU& other) : _size(other._size) {
	_parent = new int[_size];
	_rank = new int[_size];

	for (size_t i = 0; i < _size; i++) {
		_parent[i] = other._parent[i];
		_rank[i] = other._rank[i];
	}
}

DSU::~DSU() {
	delete[] _parent;
	delete[] _rank;
}

void DSU::func_union(int x, int y) {
	if (x >= _size || y >= _size || x < 0 || y < 0) throw std::out_of_range("Incorrect values");
	if (x == y) return;

	int parent_x = find(x);
	int parent_y = find(y);

	if (_rank[parent_x] >= _rank[parent_y]) {
		_parent[parent_y] = parent_x;
	}
	else if (_rank[parent_x] < _rank[parent_y]) {
		_parent[parent_x] = parent_y;
	}
	if (_rank[parent_x] == _rank[parent_y]) {
		_rank[parent_x]++; //O(1)
	}
}

int DSU::find(int x) {
	if (x >= _size || x < 0) throw std::out_of_range("Incorrect values");

	while (x != _parent[x]) {
		x = _parent[x];
	}

	return x;
}

int DSU::find_rec(int x) {
	if (_parent[x] == x) return x;
	return _parent[x] = find_rec(_parent[x]);
}
