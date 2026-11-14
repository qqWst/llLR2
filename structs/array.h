#pragma once
#include <iostream>

template <typename T>
struct Array {
    T* data;
    size_t size;
    size_t capacity;
};

Array<char> initArray(const std::string& str);

template <typename T>
void killArray(Array<T>& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}

template <typename T>
size_t lengthArray(const Array<T>& arr) {
    return arr.size;
}

template <typename T>
T getArray(const Array<T>& arr, size_t index) {
    if (index >= arr.size) {
        std::cerr << "ОШИБКА: (MGET) индекс вне массива!!!" << std::endl;
        return T{};
    }
    return arr.data[index];
}

template <typename T>
void setArray(Array<T>& arr, size_t index, T value) {
    if (index >= arr.size) {
        std::cerr << "ОШИБКА: (MSET) индекс вне массива!!!" << std::endl;
        return;
    }
    arr.data[index] = value;
}

template <typename T>
void expandCapacity(Array<T>& arr, size_t newCapacity) {
    if (newCapacity <= arr.capacity) return;

    T* newData = new T[newCapacity];
    for (size_t i = 0; i < arr.size; ++i) {
        newData[i] = arr.data[i];
    }
    delete[] arr.data;
    arr.data = newData;
    arr.capacity = newCapacity;
}

template <typename T>
void push_backArray(Array<T>& arr, T value) {
    if (arr.size == arr.capacity) {
        expandCapacity(arr, arr.capacity == 0 ? 1 : arr.capacity * 2);
    }
    arr.data[arr.size] = value;
    ++arr.size;
}

template <typename T>
void insertArray(Array<T>& arr, size_t index, T value) {
    if (index > arr.size) {
        std::cerr << "ОШИБКА: (MINSERT) индекс вне массива!!!" << std::endl;
        return;
    }
    if (arr.size >= arr.capacity) {
        expandCapacity(arr, arr.capacity == 0 ? 1 : arr.capacity * 2);
    }
    for (size_t i = arr.size; i > index; --i) {
        arr.data[i] = arr.data[i - 1];
    }
    arr.data[index] = value;
    ++arr.size;
}

template <typename T>
void removeArray(Array<T>& arr, size_t index) {
    if (index >= arr.size) {
        std::cerr << "ОШИБКА: (MREMOVE) индекс вне массива!!!" << std::endl;
        return;
    }
    for (size_t i = index; i < arr.size - 1; ++i) {
        arr.data[i] = arr.data[i + 1];
    }
    --arr.size;
}

template <typename T>
void printArray(const Array<T>& arr) {
    if (arr.size == 0) {
        std::cout << "Массив пуст." << std::endl;
        return;
    }
    std::cout << "Массив: " << std::endl;
    for (size_t i = 0; i < arr.size; ++i) {
        std::cout << arr.data[i];
        if (i < arr.size - 1) std::cout << ", ";
    }
    std::cout << std::endl;
}