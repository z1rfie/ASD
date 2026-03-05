#ifndef LIB_SKIP_LIST
#define LIB_SKIP_LIST

#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include "../lib_tvector/vector.h"

template<typename TKey, typename TValue>
struct Node {
    std::pair<TKey, TValue> data;
    Node* next_lvl; 
    Node* next_elem; 

    Node(const TKey& key, const TValue& value)
        : data(key, value), next_lvl(nullptr), next_elem(nullptr) {
    }
};

template <class TKey, class TValue>
class SkipList {
    int _MAX_LEVEL;
    int _level;
    TVector<Node<TKey, TValue>*> _heads;
public:
    SkipList();
    SkipList(size_t max_level);
    ~SkipList();

    void insert(const TKey& key, const TValue& value);
    void print() const noexcept;
private:
    size_t flip_coin() const noexcept;
    TVector<Node<TKey, TValue>*> find_insert_position(const TKey& key) const;
};

template <class TKey, class TValue>
SkipList<TKey, TValue>::SkipList() : _MAX_LEVEL(20), _level(0) { 
    srand(time(NULL));
    _heads.resize(_MAX_LEVEL + 1, nullptr);
}

template <class TKey, class TValue>
SkipList<TKey, TValue>::SkipList(size_t max_level) : _MAX_LEVEL(max_level), _level(0) {
    srand(time(NULL));
    _heads.resize(_MAX_LEVEL + 1, nullptr);
}

template <class TKey, class TValue>
SkipList<TKey, TValue>::~SkipList() {
    Node<TKey, TValue>* current = _heads[0];

    while (current != nullptr) {
        Node<TKey, TValue>* next = current->next_elem;

        Node<TKey, TValue>* vertical = current;
        while (vertical != nullptr) {
            Node<TKey, TValue>* up = vertical->next_lvl; 
            delete vertical;
            vertical = up;
        }

        current = next;
    }
}

template <class TKey, class TValue>
void SkipList<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    TVector<Node<TKey, TValue>*> prev = find_insert_position(key);

    Node<TKey, TValue>* next;

    if (prev[0] != nullptr) {
        next = prev[0]->next_elem;
    }
    else {
        next = _heads[0];
    }

    if (next != nullptr && next->data.first == key) {
        throw std::invalid_argument("Ключ уже существует в списке");
    }

    int node_level = flip_coin();

    if (node_level > _level)
        _level = node_level;

    Node<TKey, TValue>* lower_node = nullptr;

    for (int i = 0; i <= node_level; i++) {
        Node<TKey, TValue>* new_node = new Node<TKey, TValue>(key, value);

        if (lower_node != nullptr) {
            lower_node->next_lvl = new_node;
        }

        lower_node = new_node;

        if (prev[i] != nullptr) {
            new_node->next_elem = prev[i]->next_elem;
            prev[i]->next_elem = new_node;
        }
        else {
            new_node->next_elem = _heads[i];
            _heads[i] = new_node;
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
TVector<Node<TKey, TValue>*> SkipList<TKey, TValue>::find_insert_position(const TKey& key) const {
    TVector<Node<TKey, TValue>*> update;
    update.resize(_MAX_LEVEL + 1, nullptr);

    for (int i = _level; i >= 0; i--) {
        Node<TKey, TValue>* current = _heads[i];
        Node<TKey, TValue>* prev = nullptr;

        while (current != nullptr && current->data.first < key) {
            prev = current;
            current = current->next_elem;
        }

        update[i] = prev;
    }

    return update;
}

template <class TKey, class TValue>
void SkipList<TKey, TValue>::print() const noexcept {
    TVector<TKey> keys;
    Node<TKey, TValue>* current = _heads[0];

    while (current != nullptr) {
        keys.push_back_elem(current->data.first);
        current = current->next_elem;
    }

    for (int lvl = _level; lvl >= 0; lvl--) {
        std::cout << "Level " << lvl << ": ";

        for (size_t i = 0; i < keys.size(); i++) {

            Node<TKey, TValue>* node = _heads[lvl];
            bool found = false;

            while (node != nullptr) {
                if (node->data.first == keys[i]) {
                    found = true;
                    break;
                }
                node = node->next_elem;
            }

            if (found)
                std::cout << "(" << keys[i] << ") ";
            else
                std::cout << "    ";
        }

        std::cout << std::endl;
    }
}
#endif // LIB_SKIP_LIST