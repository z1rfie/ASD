#ifndef LIB_UNSORTED_TABLE_M
#define LIB_UNSORTED_TABLE_M

#include "../lib_table/table.h"
#include "../lib_tvector/vector.h"

template  <class TKey, class TValue>
class SortedTableM : public Table<TKey, TValue> {
	TVector <std::pair<TKey, TValue>> _rows;
public:
	SortedTableM() = default;
	~SortedTableM() {}

	void insert(const TKey&, const TValue& value) override;
	void erase(const TKey&) override;
	TValue& found(const TKey&) override;

	bool is_empty() const noexcept override;

	void print(std::ostream& os) const override;
	TValue& operator[](const TKey& key) override;
private:
	int binary_search(const TKey&) const;
};

template  <class TKey, class TValue>
void SortedTableM<TKey, TValue>::insert(const TKey& key, const TValue& value) {
	int pos = binary_search(key);

	if (pos >= 0)
		throw std::logic_error("The key is already occupied");

	pos = -pos - 1;

	_rows.insert_elem(std::make_pair(key, value), pos + 1);
}

template  <class TKey, class TValue>
void SortedTableM<TKey, TValue>::erase(const TKey& key) {
	int pos = binary_search(key);

	if (pos < 0) {
		throw std::logic_error("The key was not found");
	}

	_rows.erase_elem(pos + 1);
}

template <class TKey, class TValue>
TValue& SortedTableM<TKey, TValue>::found(const TKey& key) {
	int pos = binary_search(key);

	if (pos < 0) {
		throw std::logic_error("The key was not found");
	}

	return _rows[pos].second;
}

template  <class TKey, class TValue>
bool SortedTableM<TKey, TValue>::is_empty() const noexcept {
	return _rows.is_empty();
}

template  <class TKey, class TValue>
void SortedTableM<TKey, TValue>::print(std::ostream& os) const {
	for (int i = 0; i < _rows.size(); i++) {
		os << "| " << _rows[i].first << " | " << _rows[i].second << " |" << std::endl;
	}
}

template<class TKey, class TValue>
int SortedTableM<TKey, TValue>::binary_search(const TKey& key) const {
	int left = 0;
	int right = _rows.size() - 1;

	while (left <= right) {
		int mid = (left + right) / 2;

		if (_rows[mid].first == key) return mid;

		if (_rows[mid].first < key) left = mid + 1;
		else right = mid - 1;
	}

	return -left - 1; 
}

template <class TKey, class TValue>
TValue& SortedTableM<TKey, TValue>::operator[](const TKey& key) {
	int pos = binary_search(key);

	if (pos >= 0) {
		return _rows[pos].second;
	}

	pos = -pos - 1;

	_rows.insert_elem(std::make_pair(key, TValue()), pos + 1);

	return _rows[pos].second;
}

#endif  // LIB_UNSORTED_TABLE_M
