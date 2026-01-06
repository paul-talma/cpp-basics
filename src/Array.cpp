#include "../include/Array.hpp"
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

// constructors
Array::Array() : size(0), capacity(8) { data = new int[capacity]; }
Array::Array(size_t n) : size(n), capacity(8) {
    if (size > capacity) {
        capacity = size;
    }
    data = new int[capacity];
    for (size_t i = 0; i < size; i++) {
        data[i] = 0;
    }
}
Array::Array(int *arr, size_t n) : size(n), capacity(8) {
    if (size > capacity) {
        capacity = size;
    }
    data = new int[capacity];
    for (size_t i = 0; i < size; i++) {
        data[i] = arr[i];
    }
}

// copy constructors
Array::Array(const Array &other) {
    size = other.size;
    capacity = other.capacity;
    data = new int[capacity];
    for (size_t i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
};
Array &Array::operator=(const Array &other) {
    if (this != &other) {
        size = other.size;
        capacity = other.capacity;
        int *new_data = new int[capacity];
        for (size_t i = 0; i < size; i++) {
            new_data[i] = other.data[i];
        }
        delete[] data;
        data = new_data;
    }
    return *this;
}

Array::~Array() { delete[] data; }

void Array::push(int n) {
    if (size == capacity) {
        resize(capacity * 2);
    }
    data[size++] = n;
}

int Array::pop_back() {
    if (size == 0) {
        throw std::out_of_range("empty array");
    }
    size--;
    int val = data[size];
    if (size < capacity / 2) {
        resize(capacity / 2);
    }
    return val;
}

void Array::insert_at(size_t id, int n) {
    if (id > size) {
        throw std::out_of_range("invalid index");
    }
    if (size == capacity) {
        resize(capacity * 2);
    }
    for (size_t i = size; i > id; i--) {
        data[i] = data[i - 1];
    }
    data[id] = n;
    size++;
}

void Array::erase(size_t id) {
    if (id >= size) {
        throw std::out_of_range("invalid index");
    }
    size--;
    for (size_t i = id; i < size; i++) {
        data[i] = data[i + 1];
    }
    if (size < capacity / 2) {
        resize(capacity / 2);
    }
}

int &Array::operator[](size_t id) { return data[id]; }
const int &Array::operator[](size_t id) const { return data[id]; }

int &Array::at(size_t id) {
    if (id >= size) {
        throw std::out_of_range("invalid index");
    }
    return data[id];
}
const int &Array::at(size_t id) const {
    if (id >= size) {
        throw std::out_of_range("invalid index");
    }
    return data[id];
}

std::string Array::show() {
    std::string arr_str = "[";
    for (size_t i = 0; i < size; i++) {
        arr_str.append(std::to_string(data[i]));
        if (i < size - 1) {
            arr_str.append(" ");
        }
    }
    return arr_str.append("]");
}

size_t Array::len() const { return size; }
size_t Array::cap() const { return capacity; }

void Array::resize(size_t new_capacity) {
    int *new_data = new int[new_capacity];
    for (size_t i = 0; i < size; i++) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

int main() {
    int input[] = {1, 2, 3, 4, 5, 6, 7};
    Array a(input, 7);

    Array b = a;
    b[2] = 55;

    std::cout << b.show() << std::endl;
    std::cout << a.show() << std::endl;

    return 0;
}
