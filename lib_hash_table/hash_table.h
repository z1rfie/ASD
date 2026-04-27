#include "../lib_tvector/vector.h"
#include <iostream>
#include <numeric>
#include <stdexcept>

size_t gcd(size_t a, size_t b) {
    while (b != 0) {
        size_t t = b;
        b = a % b;
        a = t;
    }
    return a;
}

enum Status { _busy, _deleted, _empty };

template<class TValue>
struct HashData {
    Status _state;
    std::string _key;
    TValue _value;

    HashData() : _state(_empty), _key(""), _value(TValue()) {}
    HashData(Status s, const std::string& k, const TValue& v)
        : _state(s), _key(k), _value(v) {
    }
};

template<class TValue>
class HashTable {
    TVector<HashData<TValue>> rows;
    size_t size;
    size_t count;
    size_t shift;
public:
    HashTable(size_t sz);
    void insert(const std::string& key, const TValue& value);
    void erase(const std::string& key);
    TValue& found(const std::string& key);
    bool is_empty() const noexcept;

    void print() const;
private:
    size_t h(const std::string& key);
    size_t hh(size_t hash);
};

template<class TValue>
HashTable<TValue>::HashTable(size_t sz) : size(sz), count(0), shift(1) {
    rows.resize(sz); 

    for (size_t i = 0; i < size; i++) {
        rows[i] = HashData<TValue>(); 
    }
    for (size_t i = std::max((size_t)2, size / 15); i < size; i++) {
        if (gcd(i, size) == 1) { shift = i; break; }
    }
}

template<class TValue>
void HashTable<TValue>::insert(const std::string& key, const TValue& value) {
    size_t hash = h(key);
    size_t steps = 0;
    while (steps < size) {
        if (rows[hash]._state != _busy) {
            rows[hash] = HashData<TValue>(_busy, key, value); 
            count++;
            return;
        }
        if (rows[hash]._key == key) {
            throw std::runtime_error("Key already exists"); 
        }
        hash = hh(hash);
        steps++;
    }
    throw std::runtime_error("Hash table is full");
}

template<class TValue>
void HashTable<TValue>::erase(const std::string& key) {
    size_t hash = h(key);
    size_t steps = 0;
    while (steps < size) {
        if (rows[hash]._state == _empty) break;
        if (rows[hash]._state == _deleted) break;
        if (rows[hash]._state == _busy && rows[hash]._key == key) {
            rows[hash]._state = _deleted;
            count--;
            return;
        }
        hash = hh(hash);
        steps++;
    }
    throw std::runtime_error("Key not found");
}

template<class TValue>
TValue& HashTable<TValue>::found(const std::string& key) {
    size_t hash = h(key);
    size_t count = 0;
    while (count < size) {
        if (rows[hash]._state == _empty) break;
        if (rows[hash]._state == _deleted) break;
        if (rows[hash]._state == _busy && rows[hash]._key == key) {
            return rows[hash]._value;
        }
        hash = hh(hash);
        count++;
    }
    throw std::runtime_error("Key not found");
}

template<class TValue>
bool HashTable<TValue>::is_empty() const noexcept { // o(1)
    return count == 0;
}

template<class TValue>
size_t HashTable<TValue>::h(const std::string& key) {
    size_t hash = 0;
    for (size_t i = 0; i < key.size(); i++) {
        hash += key[i];
    }
    return hash % size;
}

template<class TValue>
size_t HashTable<TValue>::hh(size_t hash) {
    return (hash + shift) % size;
}

template<class TValue>
void HashTable<TValue>::print() const {
    for (size_t i = 0; i < size; i++) {
        if (rows[i]._state == _busy) {
            std::cout << rows[i]._key << " - " << rows[i]._value << std::endl;
        }
    }
}