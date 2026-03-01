#ifndef LIB_SKIP_LIST
#define LIB_SKIP_LIST

#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include "../lib_list/list.h"
#include "../lib_tvector/vector.h"

template <class TKey, class TValue>
struct NodeSL {
    std::pair<TKey, TValue> _data;
    NodeSL** _next;
    NodeSL(std::pair<TKey, TValue> data, NodeSL** next) : _data(data), _next(next) {}
    ~NodeSL() { delete[] _next; }
};

template <class TKey, class TValue>
class SkipList {
    size_t _MAX_LEVEL;
    size_t _level; 
    TVector<NodeSL<TKey, TValue>*> _heads;
public:
    SkipList();
    SkipList(size_t max_level);
    void insert(const TKey& key, const TValue& value);
    void print() const noexcept;

protected:
    size_t flip_coin() const noexcept;
    NodeSL<TKey, TValue>* find_nearest(const TKey& key) const noexcept;
};

template <class TKey, class TValue>
SkipList<TKey, TValue>::SkipList() : _MAX_LEVEL(20), _level(0) { 
    _heads.resize(_MAX_LEVEL + 1, nullptr);
}

template <class TKey, class TValue>
SkipList<TKey, TValue>::SkipList(size_t max_level) : _MAX_LEVEL(max_level), _level(0) {
    _heads.resize(_MAX_LEVEL + 1, nullptr);
}

template <class TKey, class TValue>
void SkipList<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    NodeSL<TKey, TValue>* prev = find_nearest(key);

    NodeSL<TKey, TValue>* next = (prev == nullptr) ? _heads[0] : prev->_next[0];
    if (next != nullptr && next->_data.first == key) {
        next->_data.second = value; 
        return;
    }

    size_t new_level = flip_coin();

    if (new_level > _level) {
        _level = new_level;
    }

    NodeSL<TKey, TValue>** next_array = new NodeSL<TKey, TValue>* [new_level + 1];
    for (size_t i = 0; i <= new_level; i++) {
        next_array[i] = nullptr;
    }

    std::pair<TKey, TValue> data(key, value);
    NodeSL<TKey, TValue>* new_node = new NodeSL<TKey, TValue>(data, next_array);

    if (prev == nullptr) {
        for (size_t i = 0; i <= new_level; i++) {
            new_node->_next[i] = _heads[i];
            _heads[i] = new_node;
        }
    }
    else {
        for (size_t i = 0; i <= new_level; i++) {
            new_node->_next[i] = prev->_next[i];
            prev->_next[i] = new_node;
        }
    }
}

template <class TKey, class TValue>
size_t SkipList<TKey, TValue>::flip_coin() const noexcept {
    size_t lvl = 0;
    while (lvl < _MAX_LEVEL && rand() % 100 < 50) {
        lvl++;
    }
    return lvl;
}

template <class TKey, class TValue>
NodeSL<TKey, TValue>* SkipList<TKey, TValue>::find_nearest(const TKey& key) const noexcept {
    if (_level >= _heads.size() || _heads[_level] == nullptr) return nullptr;

    NodeSL<TKey, TValue>* current = _heads[_level];

    for (int i = _level; i >= 0; i--) {
        while (current->_next[i] != nullptr &&
            current->_next[i]->_data.first < key) {
            current = current->_next[i];
        }
    }

    return current;
}

template <class TKey, class TValue>
void SkipList<TKey, TValue>::print() const noexcept {
    setlocale(LC_ALL, "rus");

    for (int i = _level; i >= 0; i--) {
        std::cout << "Уровень " << i << ": ";
        NodeSL<TKey, TValue>* current = _heads[i];

        while (current != nullptr) {
            std::cout << "(" << current->_data.first
                << "," << current->_data.second << ") ";
            current = current->_next[i];
        }
        std::cout << std::endl;
    }
}

#endif // LIB_SKIP_LIST