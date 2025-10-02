#include <windows.h>
#include <iostream>
#include "vector.h"
#include <gtest/gtest.h>

#define EPSILON 0.000001

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

TEST(TestTVectorLib, randomize) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    randomize(vec);

    EXPECT_EQ(vec.size(), 14);
    EXPECT_EQ(vec.capacity(), 15);
}

TEST(TestTVectorLib, randomize_empty_mass) {
    TVector<int> vec;

    randomize(vec);

    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 0);
}

TEST(TestTVectorLib, randomize_one_elem) {
    TVector<int> vec(1);

    randomize(vec);

    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec.capacity(), 15);
}

TEST(TestTVectorLib, default_constructor) {
    TVector<int> vec;

    EXPECT_EQ(vec.data(), nullptr);
    EXPECT_EQ(vec.capacity(), 0);
    EXPECT_EQ(vec.size(), 0);
    EXPECT_TRUE(vec.is_empty());
}

TEST(TestTVectorLib, default_constructor_char) {
    TVector<char> vec;

    EXPECT_EQ(vec.data(), nullptr);
    EXPECT_EQ(vec.capacity(), 0);
    EXPECT_EQ(vec.size(), 0);
    EXPECT_TRUE(vec.is_empty());
}

TEST(TestTVectorLib, size_null_constructor) {
    TVector<int> vec(0);

    EXPECT_EQ(vec.data(), nullptr);
    EXPECT_EQ(vec.capacity(), 0);
    EXPECT_EQ(vec.size(), 0);
    EXPECT_TRUE(vec.is_empty());
}

TEST(TestTVectorLib, size_constructor) {
    TVector<int> vec(7);

    EXPECT_EQ(vec.capacity(), 15);
    EXPECT_EQ(vec.size(), 7);
    for (size_t i = 0; i < vec.capacity(); i++) {
        EXPECT_EQ(vec.states()[i], empty);
    }
}

TEST(TestTVectorLib, arr_and_size_constructor) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    EXPECT_EQ(vec.capacity(), 15);
    EXPECT_EQ(vec.size(), 14);
    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_EQ(vec.data()[i], arr[i]);
    }
    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_EQ(vec.states()[i], busy);
    }
}

TEST(TestTVectorLib, arr_and_size_null_constructor) {
    const char* arr = nullptr;
    TVector<char> vec(arr, 0);

    EXPECT_EQ(vec.data(), arr);
    EXPECT_EQ(vec.capacity(), 0);
    EXPECT_EQ(vec.size(), 0);
    EXPECT_TRUE(vec.is_empty());
}

TEST(TestTVectorLib, copy_constructor) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    TVector<int> vec2(vec1);

    EXPECT_EQ(vec2.capacity(), 15);
    EXPECT_EQ(vec2.size(), 14);
    for (size_t i = 0; i < vec2.size(); i++) {
        EXPECT_EQ(vec1.data()[i], vec2.data()[i]);
    }
}

TEST(TestTVectorLib, null_copy_constructor) {
    const char* arr = nullptr;
    TVector<char> vec1(arr, 0);
    TVector<char> vec2(vec1);

    EXPECT_EQ(vec1.data(), vec2.data());
    EXPECT_EQ(vec2.capacity(), 0);
    EXPECT_EQ(vec2.size(), 0);
    EXPECT_TRUE(vec2.is_empty());
}

TEST(TestTVectorLib, assign) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    vec.assign(4, 444);

    EXPECT_EQ(vec.capacity(), 15);
    EXPECT_EQ(vec.size(), 4);
    for (size_t i = 0; i < 4; i++) {
        EXPECT_EQ(vec.data()[i], 444);
    }
}

TEST(TestTVectorLib, assign_in_empty_vec) {
    TVector<int> vec;

    vec.assign(4, 444);

    EXPECT_EQ(vec.capacity(), 4);
    EXPECT_EQ(vec.size(), 4);
    for (size_t i = 0; i < 4; i++) {
        EXPECT_EQ(vec.data()[i], 444);
    }
}

TEST(TestTVectorLib, assign_zero_count) {
    TVector<int> vec;

    vec.assign(0, 42);

    EXPECT_EQ(vec.capacity(), 0);
    EXPECT_EQ(vec.size(), 0);
}

TEST(TestTVectorLib, assign_large_count) {
    TVector<int> vec;
    int huge = 1000000;

    vec.assign(huge, 42);

    EXPECT_EQ(vec.size(), huge);
    for (size_t i = 0; i < huge; i++) {
        EXPECT_EQ(vec.data()[i], 42);
    }
}

TEST(TestTVectorLib, repeated_assign) {
    TVector<int> vec;

    vec.assign(10, 1);
    vec.assign(5, 2);

    EXPECT_EQ(vec.size(), 5);
    for (size_t i = 0; i < 5; i++) {
        EXPECT_EQ(vec.data()[i], 2);
    }
}

TEST(TestTVectorLib, clear) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    vec.clear();

    EXPECT_TRUE(vec.is_empty());
    EXPECT_EQ(vec.size(), 0);
    for (size_t i = 0; i < 5; i++) {
        EXPECT_EQ(vec.states()[i], empty);
    }
}

TEST(TestTVectorLib, null_clear) {
    TVector<int> vec;

    vec.clear();

    EXPECT_TRUE(vec.is_empty());
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 0);
}

TEST(TestTVectorLib, reserve_return) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    vec.reserve(13);

    EXPECT_EQ(vec.capacity(), 15);
}

TEST(TestTVectorLib, reserve) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);

    vec.reserve(17);

    EXPECT_EQ(vec.capacity(), 17);
}

TEST(TestTVectorLib, reserve_null_arr) {
    TVector<int> vec;

    vec.reserve(5);

    EXPECT_EQ(vec.capacity(), 5);
    EXPECT_EQ(vec.size(), 0);
    EXPECT_NE(vec.data(), nullptr);
    for (size_t i = 0; i < vec.capacity(); i++) {
        EXPECT_EQ(vec.states()[i], empty);
    }
}

TEST(TestTVectorLib, shrink_to_fit_null_size) {
    TVector<int> vec;

    vec.shrink_to_fit();

    EXPECT_EQ(vec.capacity(), 0);
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.data(), nullptr);
    EXPECT_EQ(vec.states(), nullptr);
}

TEST(TestTVectorLib, shrink_to_fit) {
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec(arr, 16);

    vec.shrink_to_fit();

    EXPECT_EQ(vec.capacity(), 16);
    for (size_t i = 0; i < vec.capacity(); i++) {
        EXPECT_EQ(vec.states()[i], busy);
    }
}

TEST(TestTVectorLib, shrink_to_fit_after_empty_reserve) {
    TVector<int> vec;

    vec.reserve(5);

    EXPECT_EQ(vec.capacity(), 5);
    EXPECT_EQ(vec.size(), 0);

    vec.shrink_to_fit();

    EXPECT_EQ(vec.data(), nullptr);
    EXPECT_EQ(vec.states(), nullptr);
    EXPECT_EQ(vec.capacity(), 0);
    EXPECT_EQ(vec.size(), 0);
}

TEST(TestTVectorLib, resize_decrease) {
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec(arr, 16);

    vec.resize(13);

    EXPECT_EQ(vec.size(), 13);
    for (size_t i = vec.size(); i < vec.capacity(); i++) {
        EXPECT_EQ(vec.states()[i], empty);
    }

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_EQ(vec.data()[i], arr[i]);
        EXPECT_EQ(vec.states()[i], busy);
    }
}

TEST(TestTVectorLib, resize_increase_empty_vec) {
    TVector<int> vec;

    vec.resize(3);

    EXPECT_EQ(vec.capacity(), 3);
    EXPECT_EQ(vec.size(), 3);
    for (size_t i = 0; i < vec.capacity(); i++) {
        EXPECT_EQ(vec.states()[i], busy);
    }
}


TEST(TestTVectorLib, resize_increase) {
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec(arr, 16);

    vec.resize(19);

    EXPECT_EQ(vec.size(), 19);
    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_EQ(vec.states()[i], busy);
    }

    for (size_t i = vec.size(); i < vec.capacity(); i++) {
        EXPECT_EQ(vec.states()[i], empty);
    }
}

TEST(TestTVectorLib, resize_with_value_decrease) {
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec(arr, 16);

    vec.resize(13, 111);

    EXPECT_EQ(vec.size(), 13);
    for (size_t i = vec.size(); i < vec.capacity(); i++) {
        EXPECT_EQ(vec.states()[i], empty);
    }

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_EQ(vec.data()[i], arr[i]);
        EXPECT_EQ(vec.states()[i], busy);
    }
}

TEST(TestTVectorLib, resize_with_value_increase_empty_vec) {
    TVector<int> vec;

    vec.resize(3, 777);

    EXPECT_EQ(vec.size(), 3);
    EXPECT_GE(vec.capacity(), 3);

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_EQ(vec.data()[i], 777);
        EXPECT_EQ(vec.states()[i], busy);
    }
}

TEST(TestTVectorLib, resize_with_value_increase) {
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec(arr, 16);

    vec.resize(19, 777);

    EXPECT_EQ(vec.size(), 19);
    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_EQ(vec.states()[i], busy);
    }

    for (size_t i = 16; i < 19; i++) {
        EXPECT_EQ(vec.data()[i], 777);
    }
}

TEST(TestTVectorLib, pop_front_elem_after_push_front_elem) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result[15] = { 2, 1, 1, 1, 1, 1,1, 1, 1, 1,1, 1, 1, 1, 1 };
    TVector<int> vec1(arr, 14), vec2(expected_result, 15);

    vec1.push_front_elem(4);
    vec1.pop_front_elem();

    EXPECT_EQ(vec1.size(), 14);
    for (size_t i = 0; i < 15; i++) {
        EXPECT_EQ(vec1.states()[i], expected_result[i]);
    }
}

TEST(TestTVectorLib, pop_back_elem_after_push_back_elem) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result[15] = { 1, 1, 1, 1, 1, 1,1, 1, 1, 1,1, 1, 1, 1, 0 };
    TVector<int> vec1(arr, 14), vec2(expected_result, 15);

    vec1.push_back_elem(4);
    vec1.pop_back_elem();

    EXPECT_EQ(vec1.size(), 14);
    for (size_t i = 0; i < 15; i++) {
        EXPECT_EQ(vec1.states()[i], expected_result[i]);
    }
}

TEST(TestTVectorLib, erase_elem_after_insert_elem) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result[15] = { 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    TVector<int> vec1(arr, 14), vec2(expected_result, 15);

    vec1.insert_elem(4, 4);
    vec1.erase_elem(4);

    EXPECT_EQ(vec1.size(), 14);
    for (size_t i = 0; i < 15; i++) {
        EXPECT_EQ(vec1.states()[i], expected_result[i]);
    }
}

TEST(TestTVectorLib, pop_front_elems_after_push_front_elems) {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    int arr2[2] = { 1, 2 };
    int expected_result[18] = { 2, 2, 1, 1, 1, 1, 1, 1,1, 1, 1, 1,1, 1, 1, 1, 1, 1 };
    TVector<int> vec1(arr1, 16), vec2(expected_result, 18);

    vec1.push_front_elems(arr2, 2);
    vec1.pop_front_elems(2);

    EXPECT_EQ(vec1.size(), 16);
    for (size_t i = 0; i < 18; i++) {
        EXPECT_EQ(vec1.states()[i], expected_result[i]);
    }
}

TEST(TestTVectorLib, pop_back_elems_after_push_back_elems) {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    int arr2[2] = { 1, 2 };
    int expected_result[18] = { 1, 1, 1, 1, 1, 1,1, 1, 1, 1,1, 1, 1, 1, 1, 1, 0, 0 };
    TVector<int> vec1(arr1, 16), vec2(expected_result, 18);

    vec1.push_back_elems(arr2, 2);
    vec1.pop_back_elems(2);

    EXPECT_EQ(vec1.size(), 16);
    for (size_t i = 0; i < 18; i++) {
        EXPECT_EQ(vec1.states()[i], expected_result[i]);
    }
}

TEST(TestTVectorLib, erase_elems_after_insert_elems) {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    int arr2[2] = { 1, 2 };
    int expected_result[18] = { 1, 1, 2, 2, 1, 1,1, 1, 1, 1,1, 1, 1, 1, 1, 1, 1, 1 };
    TVector<int> vec1(arr1, 16), vec2(expected_result, 18);

    vec1.insert_elems(3, arr2, 2);
    vec1.erase_elems(3, 2);


    EXPECT_EQ(vec1.size(), 16);
    for (size_t i = 0; i < 18; i++) {
        EXPECT_EQ(vec1.states()[i], expected_result[i]);
    }
}

TEST(TestTVectorLib, pop_front_elem_after_emplace_elem) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result[14] = { 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    TVector<int> vec1(arr, 14), vec2(expected_result, 14);

    vec1.emplace(0, 5);
    vec1.pop_front_elem();

    EXPECT_EQ(vec1.size(), 13);
    for (size_t i = 0; i < 14; i++) {
        EXPECT_EQ(vec1.states()[i], expected_result[i]);
    }
}

TEST(TestTVectorLib, pop_back_elem_after_emplace_elem) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result[14] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 };
    TVector<int> vec1(arr, 14), vec2(expected_result, 14);

    vec1.emplace(13, 5);
    vec1.pop_back_elem();

    EXPECT_EQ(vec1.size(), 13);
    for (size_t i = 0; i < 14; i++) {
        EXPECT_EQ(vec1.states()[i], expected_result[i]);
    }
}

TEST(TestTVectorLib, erase_elem_after_emplace_elem) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int expected_result[14] = { 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    TVector<int> vec1(arr, 14), vec2(expected_result, 14);

    vec1.emplace(2, 5);
    vec1.erase_elem(3);

    EXPECT_EQ(vec1.size(), 13);
    for (size_t i = 0; i < 14; i++) {
        EXPECT_EQ(vec1.states()[i], expected_result[i]);
    }
}

TEST(TestTVectorLib, destructor) {
    TVector<int> vec;

    vec.reserve(5);

    EXPECT_EQ(vec.capacity(), 5);
    EXPECT_EQ(vec.size(), 0);

    vec.shrink_to_fit();

    EXPECT_EQ(vec.data(), nullptr);
    EXPECT_EQ(vec.states(), nullptr);
    EXPECT_EQ(vec.capacity(), 0);
    EXPECT_EQ(vec.size(), 0);
}

TEST(TestTVectorLib, destructor_releases_resources) {
    // создаем вектор в отдельном блоке для контроля времени жизни
    {
        TVector<int> vec;
        vec.push_back_elem(111);

        EXPECT_NE(vec.data(), nullptr);
        EXPECT_NE(vec.states(), nullptr);
        EXPECT_GT(vec.capacity(), 0);
        EXPECT_EQ(vec.size(), 1);

        // деструктор будет вызван автоматически при выходе из блока
    }
    TVector<int> vec;

    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 0);
    EXPECT_EQ(vec.data(), nullptr);
    EXPECT_EQ(vec.states(), nullptr);
    EXPECT_TRUE(vec.is_empty());
}

TEST(TestTVectorLib, found_elem_after_pop_elem) {
    int arr[14] = { 1, 2, 3, 4, 1, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec1(arr, 14);
    int expected_result = 2;

    vec1.erase_elems(1, 2);
    int actual_result = find_first(vec1, 1);

    EXPECT_EQ(actual_result, expected_result);
}

TEST(TestTVectorLib, overload_equal) {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec1(arr1, 16);
    int arr2[7] = { 1, 2, 3, 4, 5, 6, 7 };
    TVector<int> vec2(arr2, 7);

    vec2 = vec1;

    EXPECT_EQ(vec1.size(), vec2.size());
    EXPECT_EQ(vec1.capacity(), vec2.capacity());
    for (size_t i = 0; i < vec1.size(); i++) {
        EXPECT_EQ(vec1.data()[i], vec2.data()[i]);
    }

    for (size_t i = 0; i < vec1.capacity(); i++) {
        EXPECT_EQ(vec1.states()[i], vec2.states()[i]);
    }

}

TEST(TestTVectorLib, overload_equal_same_vecs) {
    int arr[7] = { 1, 2, 3, 4, 5, 6, 7 };
    TVector<int> vec1(arr, 7);
    TVector<int> vec2(vec1);

    vec2 = vec1;

    EXPECT_EQ(vec1.size(), vec2.size());
    EXPECT_EQ(vec1.capacity(), vec2.capacity());
    for (size_t i = 0; i < vec1.size(); i++) {
        EXPECT_EQ(vec1.data()[i], vec2.data()[i]);
    }

    for (size_t i = 0; i < vec1.capacity(); i++) {
        EXPECT_EQ(vec1.states()[i], vec2.states()[i]);
    }

}

TEST(TestTVectorLib, overload_equal_empty_vec) {
    TVector<int> vec1(5);
    TVector<int> vec2;

    vec1 = vec2;

    EXPECT_EQ(vec1.size(), 0);
    EXPECT_EQ(vec1.capacity(), 0);
    EXPECT_EQ(vec1.data(), nullptr);
    EXPECT_TRUE(vec1.is_empty());
}

TEST(TestTVectorLib, overload_self_sealing) {
    int expected_data[] = { 1, 2, 3, 4, 5 };
    int expected_states[] = { 1, 1, 1, 1, 1 };
    TVector<int> vec1(expected_data, 5);
    const size_t expected_capacity = vec1.capacity();
    const size_t expected_size = vec1.size();

    vec1 = vec1;

    for (size_t i = 0; i < vec1.size(); i++) {
        EXPECT_EQ(expected_data[i], vec1.data()[i]);
        EXPECT_EQ(expected_states[i], vec1.states()[i]);
    }

    EXPECT_EQ(expected_capacity, vec1.capacity());
    EXPECT_EQ(expected_size, vec1.size());
}

TEST(TestTVectorLib, comparison_operator_false) {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec1(arr1, 16);
    int arr2[7] = { 1, 2, 3, 4, 5, 6, 7 };
    TVector<int> vec2(arr2, 7);

    EXPECT_FALSE(vec1 == vec2);
}

TEST(TestTVectorLib, comparison_operator_true) {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec1(arr1, 16);
    TVector<int> vec2(vec1);

    EXPECT_TRUE(vec1 == vec2);
}

TEST(TestTVectorLib, comparison_operator_partially_filled) {
    TVector<int> vec1(10);
    TVector<int> vec2(10);
    for (int i = 0; i < 5; i++) {
        vec1[i] = i;
        vec2[i] = i;
    }

    EXPECT_TRUE(vec1 == vec2);
}

TEST(TestTVectorLib, comparison_operator_empty_vecs) {
    TVector<int> vec1;
    TVector<int> vec2;

    EXPECT_TRUE(vec1 == vec2);
}

TEST(TestTVectorLib, comparison_operator_with_erase) {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec1(arr1, 16);
    TVector<int> vec2(5);

    vec1.erase_elem(6);

    EXPECT_FALSE(vec1 == vec2);
}

TEST(TestTVectorLib, comparison_operator_with_reserve) {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec1(arr1, 16);
    TVector<int> vec2(vec1);

    vec1.reserve(35);

    EXPECT_TRUE(vec1 == vec2);
}

TEST(TestTVectorLib, operator_not_equal_false) {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec1(arr1, 16);
    int arr2[7] = { 1, 2, 3, 4, 5, 6, 7 };
    TVector<int> vec2(arr2, 7);

    EXPECT_TRUE(vec1 != vec2);
}

TEST(TestTVectorLib, operator_not_equal_true) {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec1(arr1, 16);
    TVector<int> vec2(vec1);

    EXPECT_FALSE(vec1 != vec2);
}

TEST(TestTVectorLib, operator_not_equal_partially_filled) {
    TVector<int> vec1(10);
    TVector<int> vec2(10);
    for (int i = 0; i < 5; i++) {
        vec1[i] = i;
        vec2[i] = i;
    }

    EXPECT_FALSE(vec1 != vec2);
}

TEST(TestTVectorLib, operator_not_equal_empty_vecs) {
    TVector<int> vec1;
    TVector<int> vec2;

    EXPECT_FALSE(vec1 != vec2);
}

TEST(TestTVectorLib, operator_not_equal_with_erase) {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec1(arr1, 16);
    TVector<int> vec2(5);

    vec1.erase_elem(6);

    EXPECT_TRUE(vec1 != vec2);
}

TEST(TestTVectorLib, operator_not_equal_with_reserve) {
    int arr1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec1(arr1, 16);
    TVector<int> vec2(vec1);

    vec1.reserve(35);

    EXPECT_FALSE(vec1 != vec2);
}

TEST(TestTVectorLib, operator_square_brackets) {
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec(arr, 16);

    EXPECT_EQ(vec[7], 8);
}

TEST(TestTVectorLib, operator_square_brackets_first_last) {
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec(arr, 16);

    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[15], 16);
}

TEST(TestTVectorLib, at_index) {
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec(arr, 16);

    EXPECT_EQ(vec.at(3), 4);
}

TEST(TestTVectorLib, at_assignment) {
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec(arr, 16);

    vec.at(5) = 999;

    EXPECT_EQ(vec.at(5), 999);
}

TEST(TestTVectorLib, at_deleted) {
    int arr[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec(arr, 16);

    vec.erase_elems(5, 3);

    EXPECT_EQ(vec.at(5), 8);
}

TEST(TestTVectorLib, push_pos_after_delete) {
    int arr[15] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    int expected_states[15] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    TVector<int> vec(arr, 15);

    vec.erase_elem(5);
    vec.insert_elem(777, 5);

    for (size_t i = 0; i < 15; i++) {
        EXPECT_EQ(vec.states()[i], expected_states[i]);
    }
}

TEST(TestTVectorLib, push_back_with_deleted) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);
    int expected_states[11] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

    vec.erase_elem(12);
    vec.erase_elem(13);
    vec.pop_back_elem();
    vec.push_back_elem(777);

    for (size_t i = 0; i < 11; i++) {
        EXPECT_EQ(vec.states()[i], expected_states[i]);
    }
}

TEST(TestTVectorLib, push_back_elems_with_deleted) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int arr2[5] = { 111, 222, 333, 444, 555 };
    TVector<int> vec(arr, 14);
    int expected_states[15] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

    vec.erase_elems(11, 3);
    vec.pop_back_elem();
    vec.push_back_elems(arr2, 5);

    for (size_t i = 0; i < 15; i++) {
        EXPECT_EQ(vec.states()[i], expected_states[i]);
    }
}

TEST(TestTVectorLib, push_insert_elems_with_deleted) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int arr2[5] = { 111, 222, 333, 444, 555 };
    TVector<int> vec(arr, 14);
    int expected_states[17] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

    vec.erase_elems(5, 2);
    vec.insert_elems(5, arr2, 5);

    for (size_t i = 0; i < 17; i++) {
        EXPECT_EQ(vec.states()[i], expected_states[i]);
    }
}

TEST(TestTVectorLib, pop_back_elems_with_deleted) {
    int arr[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    TVector<int> vec(arr, 14);
    int expected_states[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 0 };

    vec.erase_elem(13);
    vec.erase_elem(14);
    vec.pop_back_elems(4);

    for (size_t i = 0; i < 9; i++) {
        EXPECT_EQ(vec.states()[i], expected_states[i]);
    }
}