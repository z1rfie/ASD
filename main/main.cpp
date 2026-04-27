//#define EASY_EXAMPLE
#define HASH_TABLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"

int main() {
  int a, b;
  float result;

  a = 1; b = 4;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  a = 1; b = 0;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  return 0;
}

#endif  // EASY_EXAMPLE

#ifdef HASH_TABLE

#include <iostream>
#include "../lib_hash_table/hash_table.h"

template<class TKey, class TValue>
void merge(TVector<std::pair<TKey, TValue>> dict1, TVector<std::pair<TKey, TValue>> dict2) {
    HashTable<TValue> table(dict1.size() + dict2.size());

    for (size_t i = 0; i < dict1.size(); i++) {
        table.insert(dict1[i].first, dict1[i].second);
    }

    for (size_t i = 0; i < dict2.size(); i++) {
        try {
            table.insert(dict2[i].first, dict2[i].second);
        }
        catch (const std::runtime_error&) {
               
        }
    }

    table.print();
}

int main() {
    HashTable<int> table(10);

    TVector<std::pair<std::string,int>> dict1;
    dict1.push_back_elem({ "table", 1349 });
    dict1.push_back_elem({ "hash", 1985 });
    dict1.push_back_elem({ "list", 4372 });

    TVector<std::pair<std::string, int>> dict2;
    dict2.push_back_elem({ "massive", 4312 });
    dict2.push_back_elem({ "list", 5863 });
    dict2.push_back_elem({ "hash", 4317 });
    dict2.push_back_elem({ "vector", 2586 });
    
    merge(dict1, dict2);
    
    return 0;
}

#endif  // HASH_TABLE