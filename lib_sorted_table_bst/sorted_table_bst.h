#ifndef LIB_SORTED_TABLE_BST
#define LIB_SORTED_TABLE_BST

#include "../lib_table/table.h"
#include "../lib_bst/bst.h"

template <class TKey, class TValue>
class SortedTableBST : public Table<TKey, TValue> {
    BSTree<TKey, TValue> _tree;
public:
    SortedTableBST() = default;
    ~SortedTableBST() {}

    void insert(const TKey&, const TValue& value) override;
    void erase(const TKey&) override;
    TValue& found(const TKey&) override;

    bool is_empty() const noexcept override;

    void print(std::ostream& os) const override;
    TValue& operator[](const TKey& key) override;
};

template <class TKey, class TValue>
void SortedTableBST<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    if (_tree.find(key) != nullptr) throw std::logic_error("The key is already occupied");
    _tree.insert(key, value);
}

template <class TKey, class TValue>
void SortedTableBST<TKey, TValue>::erase(const TKey& key) {
    if (_tree.find(key) == nullptr) throw std::logic_error("The key was not found");
    _tree.erase(key);
}

template <class TKey, class TValue>
TValue& SortedTableBST<TKey, TValue>::found(const TKey& key) {
    TValue* val = _tree.find(key);
    if (val == nullptr) throw std::logic_error("The key was not found");
    return *val;
}

template <class TKey, class TValue>
bool SortedTableBST<TKey, TValue>::is_empty() const noexcept {
    return _tree.is_empty();
}

template <class TKey, class TValue>
TValue& SortedTableBST<TKey, TValue>::operator[](const TKey& key) {
    TValue* val = _tree.find(key);
    if (val != nullptr) return *val;
    _tree.insert(key, TValue());
    return *_tree.find(key);
}

template <class TKey, class TValue>
void SortedTableBST<TKey, TValue>::print(std::ostream& os) const {
    _tree.print_table(os);
}

#endif  // LIB_SORTED_TABLE_BST