#ifndef LIB_UNSORTED_TABLE_M
#define LIB_UNSORTED_TABLE_M

#include "../lib_table/table.h"
#include "../lib_tvector/vector.h"

template  <class TKey, class TValue>
class UnsortedTableM : public Table<TKey, TValue> {
	TVector <std::pair<TKey, TValue>> _rows;
public:
	UnsortedTableM() = default;
	~UnsortedTableM() {}

	void insert(const TKey&, const TValue& value) override;
	void erase(const TKey&) override;
	TValue& found(const TKey&) override;

	bool is_empty() const noexcept override;

	void print(std::ostream& os) const override;
};

template  <class TKey, class TValue>
void UnsortedTableM<TKey, TValue>::insert(const TKey& key, const TValue& value) {
	for (int i = 0; i < _rows.size(); i++) {
		if (_rows[i].first == key) {
			throw std::logic_error("The key is already occupied");
		}
	}
	_rows.push_back_elem(std::make_pair(key, value));
}

template  <class TKey, class TValue>
void UnsortedTableM<TKey, TValue>::erase(const TKey& key) {
	for (int i = 0; i < _rows.size(); i++) {
		if (_rows[i].first == key) {
			_rows.erase_elem(i + 1);
			return;
		}
	}
	throw std::logic_error("The key was not found");
}

template <class TKey, class TValue>
TValue& UnsortedTableM<TKey, TValue>::found(const TKey& key)  {
	for (int i = 0; i < _rows.size(); i++) {
		if (_rows[i].first == key) {
			return _rows[i].second;  
		}
	}
	throw std::logic_error("The key was not found");
}

template  <class TKey, class TValue>
bool UnsortedTableM<TKey, TValue>::is_empty() const noexcept {
	return _rows.is_empty();
}

template  <class TKey, class TValue>
void UnsortedTableM<TKey, TValue>::print(std::ostream& os) const {
	for (int i = 0; i < _rows.size(); i++) {
		os << "| " << _rows[i].first << " | " << _rows[i].second << " |" << std::endl;
	}
}

#endif  // LIB_UNSORTED_TABLE_M
