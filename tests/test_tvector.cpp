#include <windows.h>
#include <iostream>
#include "vector.h"
#include <gtest/gtest.h>

#define EPSILON 0.000001

void set_color(int text_color, int bg_color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bg_color << 4) | text_color);
}

namespace TestSystem {
    int count_success = 0, count_failed = 0;

    void start_test(bool(*test)(), const char* name_of_test) {
        set_color(2, 0);
        std::cout << "[ RUN      ]";
        set_color(7, 0);
        std::cout << name_of_test << std::endl;

        bool status = test();

        if (status == true) {
            set_color(2, 0);
            std::cout << "[       OK ]" << std::endl;
            count_success++;
        }
        else {
            set_color(4, 0);
            std::cout << "[  FAILED  ]" << std::endl;
            count_failed++;
        }
        set_color(7, 0);
    }

    template <class T>
    bool check(const T& expected, const T& actual) {
        if (expected == actual) {
            return true;
        }
        else {
            std::cerr << "Expected result is " << expected << ", but actual is " << actual << "." << std::endl;
            return false;
        }
    }

    void print_init_info() {
        set_color(2, 0);
        std::cout << "[==========] " << std::endl;
        set_color(7, 0);
    }

    void print_final_info() {
        set_color(2, 0);
        std::cout << "[==========] ";
        set_color(7, 0);
        std::cout << count_success + count_failed << " test" << (count_success + count_failed > 1 ? "s" : "") << " ran." << std::endl;
        set_color(2, 0);
        std::cout << "[  PASSED  ] ";
        set_color(7, 0);
        std::cout << count_success << " test" << (count_success > 1 ? "s" : "") << std::endl;
        if (count_failed > 0) {
            set_color(4, 0);
            std::cout << "[  FAILED  ] ";
            set_color(7, 0);
            std::cout << count_failed << " test" << (count_failed > 1 ? "s." : ".") << std::endl;
        }
    }
};

TEST(TestTVectorLib, push_front_elem) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result[15] = { 4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    TVector<int> vec2(expected_result, 15);

    // Act
    vec1.push_front_elem(4);

    // Assert
    EXPECT_EQ(vec1.size(), 15);
    EXPECT_EQ(vec1, vec2);
}

TEST(TestTVectorLib, push_back_elem) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result[15] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 4 };
    TVector<int> vec1(arr, 14);
    TVector<int> vec2(expected_result, 15);

    // Act
    vec1.push_back_elem(4);

    // Assert
    EXPECT_EQ(vec1.size(), 15);
    EXPECT_EQ(vec1, vec2);
}

TEST(TestTVectorLib, insert_elem) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result[15] = { 1, 2, 999, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    TVector<int> vec2(expected_result, 15);

    // Act
    vec1.insert_elem(999,3);

    // Assert
    EXPECT_EQ(vec1.size(), 15);
    EXPECT_EQ(vec1, vec2);
}

TEST(TestTVectorLib, push_front_elem_in_empty_mass) {
    // Arrange
    int expected_result[1] = { 1 };
    TVector<int> vec1, vec2(expected_result, 1);

    // Act
    vec1.push_front_elem(1);

    // Assert
    EXPECT_EQ(vec1.size(), 1);
    EXPECT_EQ(vec1, vec2);
}

TEST(TestTVectorLib, push_back_elem_in_empty_mass) {
    // Arrange
    int expected_result[1] = { 1 };
    TVector<int> vec1, vec2(expected_result, 1);

    // Act
    vec1.push_back_elem(1);

    // Assert
    EXPECT_EQ(vec1.size(), 1);
    EXPECT_EQ(vec1, vec2);
}

TEST(TestTVectorLib, insert_elem_in_empty_mass) {
    // Arrange
    int expected_result[1] = { 1 };
    TVector<int> vec1, vec2(expected_result, 1);

    // Act
    vec1.insert_elem(1, 1);

    // Assert
    EXPECT_EQ(vec1.size(), 1);
    EXPECT_EQ(vec1, vec2);
}


TEST(TestTVectorLib, push_front_elems) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result[18] = { 555, 666, 777, 888, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int mass[4] = { 555, 666, 777, 888 };
    TVector<int> vec1(arr, 14), vec2(expected_result, 18);

    // Act
    vec1.push_front_elems(mass, 4);

    // Assert
    EXPECT_EQ(vec1.size(), 18);
    EXPECT_EQ(vec1, vec2);
}

TEST(TestTVectorLib, push_back_elems) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result[18] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 555, 666, 777, 888 };
    int mass[4] = { 555, 666, 777, 888 };
    TVector<int> vec1(arr, 14), vec2(expected_result, 18);

    // Act
    vec1.push_back_elems(mass, 4);

    // Assert
    EXPECT_EQ(vec1.size(), 18);
    EXPECT_EQ(vec1, vec2);
}

TEST(TestTVectorLib, insert_elems) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result[18] = { 1, 2, 3, 4, 555, 666, 777, 888, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int mass[4] = { 555, 666, 777, 888 };
    TVector<int> vec1(arr, 14), vec2(expected_result, 18);

    // Act
    vec1.insert_elems(5, mass, 4);

    // Assert
    EXPECT_EQ(vec1.size(), 18);
    EXPECT_EQ(vec1, vec2);
}

TEST(TestTVectorLib, push_front_elems_in_empty_mass) {
    // Arrange
    int expected_result[4] = { 555, 666, 777, 888 };
    int mass[4] = { 555, 666, 777, 888 };
    TVector<int> vec1, vec2(expected_result, 4);

    // Act
    vec1.push_front_elems(mass, 4);

    // Assert
    EXPECT_EQ(vec1.size(), 4);
    EXPECT_EQ(vec1, vec2);
}

TEST(TestTVectorLib, push_back_elems_in_empty_mass) {
    // Arrange
    int expected_result[4] = { 555, 666, 777, 888 };
    int mass[4] = { 555, 666, 777, 888 };
    TVector<int> vec1, vec2(expected_result, 4);

    // Act
    vec1.push_back_elems(mass, 4);

    // Assert
    EXPECT_EQ(vec1.size(), 4);
    EXPECT_EQ(vec1, vec2);
}

TEST(TestTVectorLib, insert_elems_in_empty_mass) {
    // Arrange
    int expected_result[4] = { 555, 666, 777, 888 };
    int mass[4] = { 555, 666, 777, 888 };
    TVector<int> vec1, vec2(expected_result, 4);

    // Act
    vec1.insert_elems(1, mass, 4);

    // Assert
    EXPECT_EQ(vec1.size(), 4);
    EXPECT_EQ(vec1, vec2);
}

TEST(TestTVectorLib, insert_elem_error) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    EXPECT_THROW(vec.insert_elem(5, 16), std::exception);
}

TEST(TestTVectorLib, insert_elems_error) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    int mass[4] = { 555, 666, 777, 888 };

    // Act & Assert
    EXPECT_THROW(vec1.insert_elems(18, mass, 4); , std::exception);
}

TEST(TestTVectorLib, pop_front_elem) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_states[14] = { 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    TVector<int> vec(arr, 14);

    // Act
    vec.pop_front_elem();

    // Assert
    EXPECT_EQ(vec.size(), 13);

    for (int i = 0; i < 14; i++) {
        EXPECT_EQ(vec.states()[i], expected_states[i]);
    }
}

TEST(TestTVectorLib, pop_back_elem) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_states[14] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 };
    TVector<int> vec(arr, 14);

    // Act
    vec.pop_back_elem();

    // Assert
    EXPECT_EQ(vec.size(), 13);

    for (int i = 0; i < 14; i++) {
        EXPECT_EQ(vec.states()[i], expected_states[i]);
    }
}

TEST(TestTVectorLib, erase_elem) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_states[14] = { 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    TVector<int> vec(arr, 14);

    // Act
    vec.erase_elem(4);

    // Assert
    EXPECT_EQ(vec.size(), 13);

    for (int i = 0; i < 14; i++) {
        EXPECT_EQ(vec.states()[i], expected_states[i]);
    }
}

TEST(TestTVectorLib, pop_front_elems) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_states[14] = { 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    TVector<int> vec(arr, 14);

    // Act
    vec.pop_front_elems(2);

    // Assert
    EXPECT_EQ(vec.size(), 12);

    for (int i = 0; i < 14; i++) {
        EXPECT_EQ(vec.states()[i], expected_states[i]);
    }
}

TEST(TestTVectorLib, pop_back_elems) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_states[14] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 };
    TVector<int> vec(arr, 14);

    // Act
    vec.pop_back_elems(2);

    // Assert
    EXPECT_EQ(vec.size(), 12);

    for (int i = 0; i < 14; i++) {
        EXPECT_EQ(vec.states()[i], expected_states[i]);
    }
}

TEST(TestTVectorLib, erase_elems) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_states[14] = { 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    TVector<int> vec(arr, 14);

    // Act
    vec.erase_elems(4, 2);

    // Assert
    EXPECT_EQ(vec.size(), 12);

    for (int i = 0; i < 14; i++) {
        EXPECT_EQ(vec.states()[i], expected_states[i]);
    }
}

TEST(TestTVectorLib, pop_front_elem_in_empty_mass) {
    // Arrange
    TVector<int> vec;

    // Act & Assert
    EXPECT_THROW(vec.pop_front_elem(), std::exception);
}

TEST(TestTVectorLib, pop_back_elem_in_empty_mass) {
    // Arrange
    TVector<int> vec;

    // Act & Assert
    EXPECT_THROW(vec.pop_back_elem(), std::exception);
}

TEST(TestTVectorLib, erase_elem_in_empty_mass) {
    // Arrange
    TVector<int> vec;

    // Act & Assert
    EXPECT_THROW(vec.erase_elem(4), std::exception);
}

TEST(TestTVectorLib, erase_elem_error) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    EXPECT_THROW(vec.erase_elem(15), std::exception);
}

TEST(TestTVectorLib, pop_front_elems_in_empty_mass) {
    // Arrange
    TVector<int> vec;

    // Act & Assert
    EXPECT_THROW(vec.pop_front_elems(2), std::exception);
}

TEST(TestTVectorLib, pop_back_elems_in_empty_mass) {
    // Arrange
    TVector<int> vec;

    // Act & Assert
    EXPECT_THROW(vec.pop_back_elems(2), std::exception);
}

TEST(TestTVectorLib, erase_elems_in_empty_mass) {
    // Arrange
    TVector<int> vec;

    // Act & Assert
    EXPECT_THROW(vec.erase_elems(4, 2), std::exception);
}

TEST(TestTVectorLib, pop_front_elems_error) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    EXPECT_THROW(vec.pop_front_elems(15), std::exception);
}

TEST(TestTVectorLib, pop_back_elems_error) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    EXPECT_THROW(vec.pop_back_elems(15), std::exception);
}

TEST(TestTVectorLib, erase_elems_error) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    EXPECT_THROW(vec.erase_elems(4, 15), std::exception);
}

TEST(TestTVectorLib, erase_elems_pos_out_of_range) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act & Assert
    EXPECT_THROW(vec.erase_elems(-1, 10), std::exception);
}

TEST(TestTVectorLib, find_first_elem) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act
    int found_index = find_first(vec, 6);

    // Assert
    EXPECT_EQ(found_index, 5);
}

TEST(TestTVectorLib, not_find_first_elem) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act
    int found_index = find_first(vec, 111);

    // Assert
    EXPECT_EQ(found_index, -1);
}

TEST(TestTVectorLib, find_last_elem) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act
    int found_index = find_last(vec, 12);

    // Assert
    EXPECT_EQ(found_index, 11);
}

TEST(TestTVectorLib, not_find_last_elem) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act
    int found_index = find_last(vec, 111);

    // Assert
    EXPECT_EQ(found_index, -1);
}

TEST(TestTVectorLib, not_find_last_elems) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 10, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    // Act
    int* actual_result = find_elems(vec, 111); 

    // Assert
    EXPECT_EQ(actual_result[0], -1);
}

TEST(TestTVectorLib, find_all_elem) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 10, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);
    int expected_results[2] = { 5, 9 };

    // Act
    int* actual_results = find_elems(vec, 10);

    // Assert
    for (int i = 0; i < 2; i++) {
        EXPECT_EQ(actual_results[i], expected_results[i]);
    }
}

TEST(TestTVectorLib, find_first_elem_in_empty_mass) {
    // Arrange
    TVector<int> vec;

    // Act & Assert
    EXPECT_THROW(find_first(vec, 6), std::exception);
}

TEST(TestTVectorLib, find_last_elem_in_empty_mass) {
    // Arrange
    TVector<int> vec;

    // Act & Assert
    EXPECT_THROW(find_last(vec, 6), std::exception);
}

TEST(TestTVectorLib, find_all_elem_in_empty_mass) {
    // Arrange
    TVector<int> vec;

    // Act & Assert
    EXPECT_THROW(find_elems(vec, 6), std::exception);
}

TEST(TestTVectorLib, emplace) {
    // Arrange
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    int expected_res[14] = { 1, 2, 3, 4, 5, 999, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec2(expected_res, 14);

    // Act
    vec1.emplace(6, 999);

    // Assert
    EXPECT_EQ(vec1, vec2);
}

TEST(TestTVectorLib, emplace_with_deleted) {
    // Arrange
    int arr[5] = { 1, 2, 3, 4, 5 };
    TVector<int> vec(arr, 5);

    // Act
    vec.erase_elem(3);
    vec.emplace(3, 999);

    // Assert
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec[2], 999);
}

TEST(TestTVectorLib, emplace_exceptions) {
    TVector<int> empty_vec;
    EXPECT_THROW(empty_vec.emplace(0, 1), std::out_of_range);
    
    TVector<int> vec;
    vec.push_back_elem(1);
    EXPECT_THROW(vec.emplace(2, 2), std::out_of_range);
}

////////////////////////////

bool test_randomize() {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    randomize(vec1);

    if (vec1.size() != 14 || vec1.capacity() != 15) {
        return false;
    }
    return true;
}
bool test_randomize_empty_mass() {
    TVector<int> vec1;
    randomize(vec1);

    if (vec1.size() != 0 || vec1.capacity() != 0) {
        return false;
    }
    return true;
}
bool test_randomize_one_elem() {
    TVector<int> vec1(1);
    randomize(vec1);

    if (vec1.size() != 1 || vec1.capacity() != 15) {
        return false;
    }
    return true;
}

bool test_default_constructor() {
    TVector<int> vec;
    const int* expected_res = nullptr;
    return TestSystem::check(expected_res, vec.data()) &&
        TestSystem::check((size_t)0, vec.capacity()) &&
        TestSystem::check((size_t)0, vec.size());
}

bool test_default_constructor_char() {
    TVector<char> vec;
    const char* expected_res = nullptr;
    return TestSystem::check(expected_res, vec.data()) &&
        TestSystem::check((size_t)0, vec.capacity()) &&
        TestSystem::check((size_t)0, vec.size());
}

bool test_size_null_constructor() {
    TVector<int> vec(0);
    const int* expected_res = nullptr;
    return TestSystem::check(expected_res, vec.data()) &&
        TestSystem::check((size_t)0, vec.capacity()) &&
        TestSystem::check((size_t)0, vec.size());
}

bool test_size_constructor() {
    TVector<int> vec(7);
    if (vec.size() != 7) return false;
    if (vec.capacity() != 15) return false;
    for (size_t i = 0; i < vec.capacity(); i++) {
        if (vec.states()[i] != empty) {
            return false;
        }
    }
    return true;
}

bool test_arr_and_size_constructor() {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);
    if (vec.size() != 14) return false;
    if (vec.capacity() != 15) return false;
    for (size_t i = 0; i < vec.size(); i++) {
        if (vec.data()[i] != arr[i]) {
            return false;
        }
    }
    for (size_t i = 0; i < vec.size(); i++) {
        if (vec.states()[i] != busy) {
            return false;
        }
    }
    return true;
}

bool test_arr_and_size_null_constructor() {
    const char* arr = nullptr;
    TVector<char> vec(arr, 0);
    return TestSystem::check(arr, vec.data()) &&
        TestSystem::check((size_t)0, vec.capacity()) &&
        TestSystem::check((size_t)0, vec.size());
}

bool test_copy_constructor() {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    TVector<int> vec2(vec1);
    if (vec2.size() != 14) return false;
    if (vec2.capacity() != 15) return false;
    for (size_t i = 0; i < vec2.size(); i++) {
        if (vec1.data()[i] != vec2.data()[i]) return false;
    }
    return true;
}

bool test_null_copy_constructor() {
    const char* arr = nullptr;
    TVector<char> vec1(arr, 0);
    TVector<char> vec2(vec1);
    return TestSystem::check(vec1.data(), vec2.data()) &&
        TestSystem::check((size_t)0, vec2.capacity()) &&
        TestSystem::check((size_t)0, vec2.size());
}

bool test_assign() {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);
    vec.assign(4, 444);
    int expected_res[4] = { 444, 444, 444, 444 };
    for (int i = 0; i < 4; i++) {
        if (vec[i] != expected_res[i]) {
            return false;
        }
    }
    return true;
}

bool test_assign_in_empty_vec() {
    TVector<int> vec;
    vec.assign(4, 444);
    int expected_res[4] = { 444, 444, 444, 444 };
    for (int i = 0; i < 4; i++) {
        if (vec[i] != expected_res[i]) {
            return false;
        }
    }
    return true;
}

bool test_assign_zero_count() {
    TVector<int> vec;
    vec.assign(0, 42);
    return vec.size() == 0 && vec.capacity() == 0;
}

bool test_assign_large_count() {
    TVector<int> vec;
    int huge = 1000000;
    vec.assign(huge, 42);

    if (vec.size() != huge) {
        return false;
    }

    for (int i = 0; i < huge; i += 1000) { // ïðîâåðÿåì ñ øàãîì 1000 ÷òîáû íå çàíèìàëî ìíîãî âðåìåíè
        if (vec[i] != 42) {
            return false;
        }
    }
    return true;
}

bool test_repeated_assign() {
    TVector<int> vec;
    vec.assign(10, 1);
    vec.assign(5, 2);

    if (vec.size() != 5) {
        return false;
    }

    for (int i = 0; i < 5; ++i) {
        if (vec[i] != 2) {
            return false;
        }
    }
    return true;
}

bool test_clear() {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);
    vec.clear();
    if (vec.size() != 0) return false;
    for (size_t i = 0; i < vec.capacity(); ++i) {
        if (vec.states()[i] != empty) return false;
    }
    return true;
}

bool test_null_clear() {
    TVector<char> vec;
    vec.clear();
    if (vec.size() != 0) return false;
    if (vec.capacity() != 0) return false;
    return true;
}

bool test_reserve_return() {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);
    vec.reserve(13);
    if (vec.capacity() != 15) return false;
    return true;
}

bool test_reserve() {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);
    vec.reserve(17);
    if (vec.capacity() != 17) return false;
    return true;
}

bool test_reserve_null_arr() {
    TVector<int> vec;
    vec.reserve(5);
    if (vec.capacity() != 5) return false;
    if (vec.size() != 0) return false;
    if (vec.data() == nullptr) return false;
    for (size_t i = 0; i < vec.capacity(); i++) {
        if (vec.states()[i] != empty) return false;
    }
    return true;
}

bool test_shrink_to_fit_null_size() {
    TVector<int> vec;
    vec.shrink_to_fit();
    if (vec.capacity() != 0) return false;
    if (vec.size() != 0) return false;
    if (vec.data() != nullptr) return false;
    if (vec.states() != nullptr) return false;
    return true;
}

bool test_shrink_to_fit() {
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec(arr, 16);
    vec.shrink_to_fit();
    if (vec.capacity() != 16) return false;
    for (size_t i = 0; i < vec.capacity(); i++) {
        if (vec.states()[i] != busy) return false;
    }

    return true;
}

bool test_shrink_to_fit_after_empty_reserve() {
    TVector<int> vec;
    vec.reserve(5);

    if (vec.capacity() < 5) return false;
    if (vec.size() != 0) return false;

    vec.shrink_to_fit();

    if (vec.capacity() != 0) return false;
    if (vec.size() != 0) return false;
    if (vec.data() != nullptr) return false;
    if (vec.states() != nullptr) return false;

    return true;
}

bool test_resize_decrease() {
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec(arr, 16);

    vec.resize(13);

    if (vec.size() != 13) return false;
    for (size_t i = vec.size(); i < vec.capacity(); i++) {
        if (vec.states()[i] != empty) return false;
    }
    for (size_t i = 0; i < vec.size(); i++) {
        if (arr[i] != vec.data()[i]) return false;
        if (vec.states()[i] != busy) return false;
    }

    return true;
}

bool test_resize_increase_empty_vec() {
    TVector<int> vec;

    vec.resize(3);

    if (vec.size() != 3) return false;
    if (vec.capacity() != 3) return false;

    for (size_t i = 0; i < vec.size(); i++) {
        if (vec.states()[i] != busy) return false;
    }

    return true;
}

bool test_resize_increase() {
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec(arr, 16);

    vec.resize(19);

    if (vec.size() != 19) return false;

    for (size_t i = 0; i < vec.size(); i++) {
        if (vec.states()[i] != busy) return false;
    }
    for (size_t i = vec.size(); i < vec.capacity(); i++) {
        if (vec.states()[i] != empty) return false;
    }

    return true;
}

bool test_resize_with_value_decrease() {
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec(arr, 16);

    vec.resize(13, 111);

    if (vec.size() != 13) return false;
    for (size_t i = vec.size(); i < vec.capacity(); i++) {
        if (vec.states()[i] != empty) return false;
    }
    for (size_t i = 0; i < vec.size(); i++) {
        if (arr[i] != vec.data()[i]) return false;
        if (vec.states()[i] != busy) return false;
    }

    return true;
}

bool test_resize_with_value_increase_empty_vec() {
    TVector<int> vec;

    vec.resize(3, 777);

    if (vec.size() != 3) return false;
    if (vec.capacity() != 3) return false;

    for (size_t i = 0; i < vec.size(); i++) {
        if (vec.data()[i] != 777) return false;
        if (vec.states()[i] != busy) return false;
    }

    return true;
}

bool test_resize_with_value_increase() {
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec(arr, 16);

    vec.resize(19, 777);

    if (vec.size() != 19) return false;

    for (size_t i = 0; i < vec.size(); i++) {
        if (vec.states()[i] != busy) return false;
    }

    for (size_t i = 16; i < 19; i++) {
        if (vec.data()[i] != 777) return false;
    }

    return true;
}

bool test_pop_front_elem_after_push_front_elem() {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result[15] = { 2, 1, 1, 1, 1, 1,1, 1, 1, 1,1, 1, 1, 1, 1 };
    TVector<int> vec1(arr, 14), vec2(expected_result, 15);
    vec1.push_front_elem(4);
    vec1.pop_front_elem();

    if (vec1.size() != 14) {
        return false;
    }

    for (int i = 0; i < 15; i++) {
        if (vec1.states()[i] != expected_result[i]) {
            return false;
        }
    }
    return true;

}
bool test_pop_back_elem_after_push_back_elem() {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result[15] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 };
    TVector<int> vec1(arr, 14), vec2(expected_result, 15);
    vec1.push_back_elem(4);
    vec1.pop_back_elem();

    if (vec1.size() != 14) {
        return false;
    }

    for (int i = 0; i < 15; i++) {
        if (vec1.states()[i] != expected_result[i]) {
            return false;
        }
    }
    return true;

}
bool test_erase_elem_after_insert_elem() {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result[15] = { 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    TVector<int> vec1(arr, 14), vec2(expected_result, 15);
    vec1.insert_elem(4, 4);
    vec1.erase_elem(4);

    if (vec1.size() != 14) {
        return false;
    }

    for (int i = 0; i < 15; i++) {
        if (vec1.states()[i] != expected_result[i]) {
            return false;
        }
    }
    return true;

}
bool test_pop_front_elems_after_push_front_elems() {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    int arr2[2] = { 1, 2 };
    int expected_result[18] = { 2, 2, 1, 1, 1, 1, 1, 1,1, 1, 1, 1,1, 1, 1, 1, 1, 1 };
    TVector<int> vec1(arr1, 16), vec2(expected_result, 18);
    vec1.push_front_elems(arr2, 2);
    vec1.pop_front_elems(2);

    if (vec1.size() != 16) {
        return false;
    }
    for (int i = 0; i < 18; i++) {
        if (vec1.states()[i] != expected_result[i]) {
            return false;
        }
    }
    return true;

}
bool test_pop_back_elems_after_push_back_elems() {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    int arr2[2] = { 1, 2 };
    int expected_result[18] = { 1, 1, 1, 1, 1, 1,1, 1, 1, 1,1, 1, 1, 1, 1, 1, 0, 0 };
    TVector<int> vec1(arr1, 16), vec2(expected_result, 18);
    vec1.push_back_elems(arr2, 2);
    vec1.pop_back_elems(2);

    if (vec1.size() != 16) {
        return false;
    }
    for (int i = 0; i < 18; i++) {
        if (vec1.states()[i] != expected_result[i]) {
            return false;
        }
    }
    return true;

}
bool test_erase_elems_after_insert_elems() {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    int arr2[2] = { 1, 2 };
    int expected_result[18] = { 1, 1, 2, 2, 1, 1,1, 1, 1, 1,1, 1, 1, 1, 1, 1, 1, 1 };
    TVector<int> vec1(arr1, 16), vec2(expected_result, 18);
    vec1.insert_elems(3, arr2, 2);
    vec1.erase_elems(3, 2);

    if (vec1.size() != 16) {
        return false;
    }
    for (int i = 0; i < 18; i++) {
        if (vec1.states()[i] != expected_result[i]) {
            return false;
        }
    }
    return true;

}
bool test_pop_front_elem_after_emplace_elem() {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result[14] = { 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    TVector<int> vec1(arr, 14), vec2(expected_result, 14);
    vec1.emplace(0, 5);
    vec1.pop_front_elem();

    if (vec1.size() != 13) {
        return false;
    }

    for (int i = 0; i < 14; i++) {
        if (vec1.states()[i] != expected_result[i]) {
            return false;
        }
    }
    return true;

}
bool test_pop_back_elem_after_emplace_elem() {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result[14] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 };
    TVector<int> vec1(arr, 14), vec2(expected_result, 14);
    vec1.emplace(13, 5);
    vec1.pop_back_elem();

    if (vec1.size() != 13) {
        return false;
    }

    for (int i = 0; i < 14; i++) {
        if (vec1.states()[i] != expected_result[i]) {
            return false;
        }
    }
    return true;

}
bool test_erase_elem_after_emplace_elem() {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result[14] = { 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    TVector<int> vec1(arr, 14), vec2(expected_result, 14);
    vec1.emplace(2, 5);
    vec1.erase_elem(3);

    if (vec1.size() != 13) {
        return false;
    }

    for (int i = 0; i < 14; i++) {
        if (vec1.states()[i] != expected_result[i]) {
            return false;
        }
    }
    return true;

}

bool test_destructor() {
    {
        TVector<int> vec;
        vec.push_back_elem(111);
        // äåñòðóêòîð áóäåò âûçâàí àâòîìàòè÷åñêè ïðè âûõîäå èç áëîêà
    }

    TVector<int> vec;
    if (vec.size() != 0) {
        return false;
    }
    if (vec.capacity() != 0) {
        return false;
    }
    if (vec.data() != nullptr) {
        return false;
    }
    if (vec.states() != nullptr) {
        return false;
    }
    return true;
}

bool test_found_elem_after_pop_elem() {
    int arr[14] = { 1, 2, 3, 4, 1, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result = 2;
    TVector<int> vec1(arr, 14);
    vec1.erase_elems(1, 2);
    int actual_result = find_first(vec1, 1);
    return TestSystem::check(expected_result, actual_result);

}

bool test_overload_equal() {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec1(arr1, 16);
    int arr2[7] = { 1, 2, 3, 4, 5, 6, 7 };
    TVector<int> vec2(arr2, 7);
    vec2 = vec1;
    for (size_t i = 0; i < vec1.size(); i++) {
        if (vec1.data()[i] != vec2.data()[i]) return false;
        if (vec1.states()[i] != vec2.states()[i]) return false;
    }
    return TestSystem::check(vec1.capacity(), vec2.capacity()) &&
        TestSystem::check(vec1.size(), vec2.size());
}

bool test_overload_equal_same_vecs() {
    int arr[7] = { 1, 2, 3, 4, 5, 6, 7 };
    TVector<int> vec1(arr, 7);
    TVector<int> vec2(vec1);
    vec2 = vec1;
    for (size_t i = 0; i < vec1.size(); i++) {
        if (vec1.data()[i] != vec2.data()[i]) return false;
        if (vec1.states()[i] != vec2.states()[i]) return false;
    }
    return TestSystem::check(vec1.capacity(), vec2.capacity()) &&
        TestSystem::check(vec1.size(), vec2.size());
}

bool test_overload_equal_empty_vec() {
    TVector<int> vec1(5);
    TVector<int> vec2;

    vec1 = vec2;

    if (vec1.size() != 0) return false;
    if (vec1.capacity() != 0) return false;
    if (vec1.data() != nullptr) return false;

    return true;
}

bool test_overload_self_sealing() {
    int expected_data[5] = { 1, 2, 3, 4, 5 };
    int expected_states[5] = { 1, 1, 1, 1, 1 };
    TVector<int> vec1(expected_data, 5);
    const size_t expected_capacity = vec1.capacity();
    const size_t expected_size = vec1.size();

    vec1 = vec1;

    for (size_t i = 0; i < vec1.size(); i++) {
        if (vec1.data()[i] != expected_data[i]) return false;
        if (vec1.states()[i] != expected_states[i]) return false;
    }

    return TestSystem::check(vec1.capacity(), expected_capacity) &&
        TestSystem::check(vec1.size(), expected_size);
}

bool test_comparison_operator_false() {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec1(arr1, 16);
    int arr2[7] = { 1, 2, 3, 4, 5, 6, 7 };
    TVector<int> vec2(arr2, 7);

    bool expected_res = false;
    bool actual_res = (vec1 == vec2);

    return TestSystem::check(expected_res, actual_res);
}

bool test_comparison_operator_true() {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec1(arr1, 16);
    TVector<int> vec2(vec1);

    bool expected_res = true;
    bool actual_res = (vec1 == vec2);

    return TestSystem::check(expected_res, actual_res);
}

bool test_comparison_operator_partially_filled() {
    TVector<int> vec1(10);
    TVector<int> vec2(10);
    for (int i = 0; i < 5; ++i) {
        vec1[i] = i;
        vec2[i] = i;
    }
    bool expected_res = true;
    bool actual_res = (vec1 == vec2);

    return TestSystem::check(expected_res, actual_res);
}

bool test_comparison_operator_empty_vecs() {
    TVector<int> vec1;
    TVector<int> vec2;

    bool expected_res = true;
    bool actual_res = (vec1 == vec2);

    return TestSystem::check(expected_res, actual_res);
}

bool test_comparison_operator_with_erase() {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec1(arr1, 16);
    TVector<int> vec2(5);

    vec1.erase_elem(6);

    bool expected_res = false;
    bool actual_res = (vec1 == vec2);

    return TestSystem::check(expected_res, actual_res);
}

bool test_comparison_operator_with_reserve() {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec1(arr1, 16);
    TVector<int> vec2(vec1);

    vec1.reserve(35);

    bool expected_res = true;
    bool actual_res = (vec1 == vec2);

    return TestSystem::check(expected_res, actual_res);
}

bool test_operator_not_equal_false() {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec1(arr1, 16);
    int arr2[7] = { 1, 2, 3, 4, 5, 6, 7 };
    TVector<int> vec2(arr2, 7);

    bool expected_res = true;
    bool actual_res = (vec1 != vec2);

    return TestSystem::check(expected_res, actual_res);
}

bool test_operator_not_equal_true() {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec1(arr1, 16);
    TVector<int> vec2(vec1);

    bool expected_res = false;
    bool actual_res = (vec1 != vec2);

    return TestSystem::check(expected_res, actual_res);
}

bool test_operator_not_equal_partially_filled() {
    TVector<int> vec1(10);
    TVector<int> vec2(10);
    for (int i = 0; i < 5; ++i) {
        vec1[i] = i;
        vec2[i] = i;
    }

    bool expected_res = false;
    bool actual_res = (vec1 != vec2);

    return TestSystem::check(expected_res, actual_res);
}

bool test_operator_not_equal_empty_vecs() {
    TVector<int> vec1;
    TVector<int> vec2;

    bool expected_res = false;
    bool actual_res = (vec1 != vec2);

    return TestSystem::check(expected_res, actual_res);
}

bool test_operator_not_equal_with_erase() {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec1(arr1, 16);
    TVector<int> vec2(5);

    vec1.erase_elem(6);

    bool expected_res = true;
    bool actual_res = (vec1 != vec2);

    return TestSystem::check(expected_res, actual_res);
}

bool test_operator_not_equal_with_reserve() {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec1(arr1, 16);
    TVector<int> vec2(vec1);

    vec1.reserve(35);

    bool expected_res = false;
    bool actual_res = (vec1 != vec2);

    return TestSystem::check(expected_res, actual_res);
}

bool test_operator_square_brackets() {
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec(arr, 16);

    int expected_res = 8;
    int actual_res = vec[7];

    return TestSystem::check(expected_res, actual_res);
}

bool test_operator_square_brackets_first_last() {
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec(arr, 16);

    return TestSystem::check(1, vec[0]) &&
        TestSystem::check(16, vec[15]);
}

bool test_at_index() {
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec(arr, 16);
    int expected_res = 4;
    int actual_res = vec.at(3);
    return TestSystem::check(actual_res, expected_res);
}

bool test_at_assignment() {
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec(arr, 16);

    vec.at(5) = 999;

    int expected_res = 999;
    int actual_res = vec.at(5);
    return TestSystem::check(actual_res, expected_res);
}

bool test_at_deleted() {
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec(arr, 16);

    vec.erase_elems(5, 3);

    int expected_res = 8;
    int actual_res = vec.at(5);
    return TestSystem::check(actual_res, expected_res);
}

bool test_push_pos_after_delete() {
    int arr[15] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    int expected_res[15] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    TVector<int> vec(arr, 15);
    vec.erase_elem(5);
    vec.insert_elem(777, 5);

    for (size_t i = 0; i < 15; i++) {
        if (vec.states()[i] != expected_res[i]) return false;
    }

    return true;
}

bool test_push_back_with_deleted() {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    vec.erase_elem(12);
    vec.erase_elem(13);
    vec.pop_back_elem();
    vec.push_back_elem(777);

    int expected_states[11] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    for (size_t i = 0; i < 11; i++) {
        if (vec.states()[i] != expected_states[i]) return false;
    }
    return true;
}

bool test_push_back_elems_with_deleted() {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int arr2[5] = { 111, 222, 333, 444, 555 };
    TVector<int> vec(arr, 14);

    vec.erase_elems(11, 3);
    vec.pop_back_elem();
    vec.push_back_elems(arr2, 5);

    int expected_states[15] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    for (size_t i = 0; i < 15; i++) {
        if (vec.states()[i] != expected_states[i]) return false;
    }
    return true;
}

bool test_push_insert_elems_with_deleted() {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int arr2[5] = { 111, 222, 333, 444, 555 };
    TVector<int> vec(arr, 14);

    vec.erase_elems(5, 2);
    vec.insert_elems(5, arr2, 5);

    int expected_states[17] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    for (size_t i = 0; i < 17; i++) {
        if (vec.states()[i] != expected_states[i]) return false;
    }
    return true;
}

bool test_pop_back_elems_with_deleted() {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    vec.erase_elem(13);
    vec.erase_elem(14);
    vec.pop_back_elems(4);

    int expected_states[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 0 };
    for (size_t i = 0; i < 9; i++) {
        if (vec.states()[i] != expected_states[i]) return false;
    }
    return true;
}

//int main() {
//    TestSystem::print_init_info();
//
//    TestSystem::start_test(test_default_constructor, "TVector.test_default_constructor");
//    TestSystem::start_test(test_default_constructor_char, "TVector.test_default_constructor_char");
//    TestSystem::start_test(test_size_null_constructor, "TVector.test_size_null_constructor");
//    TestSystem::start_test(test_size_constructor, "TVector.test_size_constructor");
//    TestSystem::start_test(test_arr_and_size_constructor, "TVector.test_arr_and_size_constructor");
//    TestSystem::start_test(test_arr_and_size_null_constructor, "TVector.test_arr_and_size_null_constructor");
//    TestSystem::start_test(test_copy_constructor, "TVector.test_copy_constructor");
//    TestSystem::start_test(test_null_copy_constructor, "TVector.test_null_copy_constructor");
//    TestSystem::start_test(test_assign, "TVector.test_assign");
//    TestSystem::start_test(test_assign_in_empty_vec, "TVector.test_assign_in_empty_vec");
//    TestSystem::start_test(test_assign_zero_count, "TVector.test_assign_zero_count");
//    TestSystem::start_test(test_assign_large_count, "TVector.test_assign_large_count");
//
//    TestSystem::start_test(test_push_front_elem, "TVector.test_push_front_elem");
//    TestSystem::start_test(test_push_back_elem, "TVector.test_back_front_elem");
//    TestSystem::start_test(test_insert_elem, "TVector.test_insert_elem");
//    TestSystem::start_test(test_push_front_elem_in_empty_mass, "TVector.test_push_front_elem_in_empty_mass");
//    TestSystem::start_test(test_push_back_elem_in_empty_mass, "TVector.test_push_back_elem_in_empty_mass");
//    TestSystem::start_test(test_insert_elem_in_empty_mass, "TVector.test_insert_elem_in_empty_mass");
//    TestSystem::start_test(test_push_front_elems, "TVector.test_push_front_elems");
//    TestSystem::start_test(test_push_back_elems, "TVector.test_push_back_elems");
//    TestSystem::start_test(test_insert_elems, "TVector.test_insert_elems");
//    TestSystem::start_test(test_push_front_elems_in_empty_mass, "TVector.test_push_front_elems_in_empty_mass");
//    TestSystem::start_test(test_push_back_elems_in_empty_mass, "TVector.test_back_front_elems_in_empty_mass");
//    TestSystem::start_test(test_insert_elems_in_empty_mass, "TVector.test_insert_elems_in_empty_mass");
//    TestSystem::start_test(test_insert_elems_error, "TVector.test_insert_elems_error");
//    TestSystem::start_test(test_insert_elem_error, "TVector.test_insert_elem_error");
//    TestSystem::start_test(test_insert_elems_error, "TVector.test_insert_elems_error");
//    TestSystem::start_test(test_push_pos_after_delete, "TVector.test_push_pos_after_delete");
//    TestSystem::start_test(test_push_back_with_deleted, "TVector.test_push_back_with_deleted");
//    TestSystem::start_test(test_push_back_elems_with_deleted, "TVector.test_push_back_elems_with_deleted");
//    TestSystem::start_test(test_push_insert_elems_with_deleted, "TVector.test_push_insert_elems_with_deleted");
//
//    TestSystem::start_test(test_pop_front_elem, "TVector.test_pop_front_elem");
//    TestSystem::start_test(test_pop_front_elems, "TVector.test_pop_front_elems");
//    TestSystem::start_test(test_pop_front_elem_in_empty_mass, "TVector.test_pop_front_elem_in_empty_mass");
//    TestSystem::start_test(test_pop_front_elems_in_empty_mass, "TVector.test_pop_front_elems_in_empty_mass");
//    TestSystem::start_test(test_pop_back_elems_error, "TVector.test_pop_back_elems_error");
//    TestSystem::start_test(test_pop_back_elem, "TVector.test_pop_back_elem");
//    TestSystem::start_test(test_pop_back_elems, "TVector.test_pop_back_elems");
//    TestSystem::start_test(test_pop_back_elem_in_empty_mass, "TVector.test_pop_back_elem_in_empty_mass");
//    TestSystem::start_test(test_pop_back_elems_in_empty_mass, "TVector.test_pop_back_elems_in_empty_mass");
//    TestSystem::start_test(test_pop_back_elems_error, "TVector.test_pop_back_elems_error");
//    TestSystem::start_test(test_erase_elem, "TVector.test_erase_elem");
//    TestSystem::start_test(test_erase_elems, "TVector.test_erase_elems");
//    TestSystem::start_test(test_erase_elem_in_empty_mass, "TVector.test_erase_elem_in_empty_mass");
//    TestSystem::start_test(test_erase_elems_in_empty_mass, "TVector.test_erase_elems_in_empty_mass");
//    TestSystem::start_test(test_erase_elem_error, "TVector.test_erase_elem_error");
//    TestSystem::start_test(test_erase_elem_error, "TVector.test_erase_elems_error");
//    TestSystem::start_test(test_erase_elems_pos_out_of_range, "TVector.test_erase_elems_pos_out_of_range");
//    TestSystem::start_test(test_destructor, "TVector.test_destructor");
//    TestSystem::start_test(test_pop_back_elems_with_deleted, "TVector.test_pop_back_elems_with_deleted");
//
//    TestSystem::start_test(test_find_first_elem, "TVector.test_find_first_elem");
//    TestSystem::start_test(test_not_find_first_elem, "TVector.test_not_find_first_elem");
//    TestSystem::start_test(test_find_last_elem, "TVector.test_find_last_elem");
//    TestSystem::start_test(test_not_find_last_elem, "TVector.test_not_find_last_elem");
//    TestSystem::start_test(test_find_all_elem, "TVector.test_find_all_elem");
//    TestSystem::start_test(test_not_find_elems, "TVector.test_not_find_elems");
//    TestSystem::start_test(test_find_first_elem_in_empty_mass, "TVector.test_find_first_elem_in_empty_mass");
//    TestSystem::start_test(test_find_last_elem_in_empty_mass, "TVector.test_find_last_elem_in_empty_mass");
//    TestSystem::start_test(test_find_all_elem_in_empty_mass, "TVector.test_find_all_elem_in_empty_mass");
//
//    TestSystem::start_test(test_emplace, "TVector.test_emplace");
//    TestSystem::start_test(test_emplace_with_deleted, "TVector.test_emplace_with_deleted");
//    TestSystem::start_test(test_emplace_exceptions, "TVector.test_emplace_exceptions");
//
//    TestSystem::start_test(test_clear, "TVector.test_clear");
//    TestSystem::start_test(test_null_clear, "TVector.test_null_clear");
//    TestSystem::start_test(test_reserve_return, "TVector.test_reserve_return");
//    TestSystem::start_test(test_reserve, "TVector.test_reserve");
//    TestSystem::start_test(test_reserve_null_arr, "TVector.test_reserve_null_arr");
//    TestSystem::start_test(test_shrink_to_fit_null_size, "TVector.test_shrink_to_fit_null_size");
//    TestSystem::start_test(test_shrink_to_fit, "TVector.test_shrink_to_fit");
//    TestSystem::start_test(test_shrink_to_fit_after_empty_reserve, "TVector.test_shrink_to_fit_after_empty_reserve");
//    TestSystem::start_test(test_resize_decrease, "TVector.test_resize_decrease");
//    TestSystem::start_test(test_resize_increase, "TVector.test_resize_increase");
//    TestSystem::start_test(test_resize_increase_empty_vec, "TVector.test_resize_increase_empty_vec");
//    TestSystem::start_test(test_resize_with_value_decrease, "TVector.test_resize_with_value_decrease");
//    TestSystem::start_test(test_resize_with_value_increase_empty_vec, "TVector.test_resize_with_value_increase_empty_vec");
//    TestSystem::start_test(test_resize_with_value_increase, "TVector.test_resize_with_value_increase");
//
//    TestSystem::start_test(test_overload_equal, "TVector.test_overload_equal");
//    TestSystem::start_test(test_overload_equal_same_vecs, "TVector.test_overload_equal_same_vecs");
//    TestSystem::start_test(test_overload_equal_empty_vec, "TVector.test_overload_equal_empty_vec");
//    TestSystem::start_test(test_overload_self_sealing, "TVector.test_overload_self_sealing");
//    TestSystem::start_test(test_comparison_operator_false, "TVector.test_comparison_operator_false");
//    TestSystem::start_test(test_comparison_operator_true, "TVector.test_comparison_operator_true");
//    TestSystem::start_test(test_comparison_operator_partially_filled, "TVector.test_comparison_operator_partially_filled");
//    TestSystem::start_test(test_comparison_operator_empty_vecs, "TVector.test_comparison_operator_empty_vecs");
//    TestSystem::start_test(test_comparison_operator_with_erase, "TVector.test_comparison_operator_with_erase");
//    TestSystem::start_test(test_comparison_operator_with_reserve, "TVector.test_comparison_operator_with_reserve");
//    TestSystem::start_test(test_operator_not_equal_false, "TVector.test_operator_not_equal_false");
//    TestSystem::start_test(test_operator_not_equal_true, "TVector.test_operator_not_equal_true");
//    TestSystem::start_test(test_operator_not_equal_partially_filled, "TVector.test_operator_not_equal_partially_filled");
//    TestSystem::start_test(test_operator_not_equal_empty_vecs, "TVector.test_operator_not_equal_empty_vecs");
//    TestSystem::start_test(test_operator_not_equal_with_erase, "TVector.test_operator_not_equal_with_erase");
//    TestSystem::start_test(test_operator_not_equal_with_reserve, "TVector.test_operator_not_equal_with_reserve");
//    TestSystem::start_test(test_operator_square_brackets, "TVector.test_operator_square_brackets");
//    TestSystem::start_test(test_operator_square_brackets_first_last, "TVector.test_operator_square_brackets_first_last");
//
//    TestSystem::start_test(test_at_index, "TVector.test_at_index");
//    TestSystem::start_test(test_at_assignment, "TVector.test_at_assignment");
//    TestSystem::start_test(test_at_deleted, "TVector.test_at_deleted");
//
//    TestSystem::start_test(test_randomize, "TVector.test_randomize");
//    TestSystem::start_test(test_randomize_empty_mass, "TVector.test_randomize_empty_mass");
//    TestSystem::start_test(test_randomize_one_elem, "TVector.test_randomize_one_elem");
//
//    TestSystem::start_test(test_pop_front_elem_after_push_front_elem, "TVector.test_pop_front_elem_after_push_front_elem");
//    TestSystem::start_test(test_pop_back_elem_after_push_back_elem, "TVector.test_pop_back_elem_after_push_back_elem");
//    TestSystem::start_test(test_erase_elem_after_insert_elem, "TVector.test_erase_elem_after_insert_elem");
//    TestSystem::start_test(test_pop_front_elems_after_push_front_elems, "TVector.test_pop_front_elems_after_push_front_elems");
//    TestSystem::start_test(test_pop_back_elems_after_push_back_elems, "TVector.test_pop_back_elems_after_push_back_elems");
//    TestSystem::start_test(test_erase_elems_after_insert_elems, "TVector.test_erase_elems_after_insert_elems");
//    TestSystem::start_test(test_found_elem_after_pop_elem, "TVector.test_found_elem_after_pop_elem");
//    TestSystem::start_test(test_pop_front_elem_after_emplace_elem, "TVector.test_pop_front_elem_after_emplace_elem");
//    TestSystem::start_test(test_pop_back_elem_after_emplace_elem, "TVector.test_pop_back_elem_after_emplace_elem");
//    TestSystem::start_test(test_erase_elem_after_emplace_elem, "TVector.test_erase_elem_after_emplace_elem");
//
//    TestSystem::print_final_info();
//
//    system("pause");
//    return 0;
//}