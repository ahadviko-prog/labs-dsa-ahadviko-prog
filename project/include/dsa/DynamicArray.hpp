#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP
#include <cstddef>
#include <stdexcept>

template <typename T>
class DynamicArray {
private:
    T* data;
    size_t capacity;
    size_t current_size;
    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < current_size; ++i) new_data[i] = data[i];
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
public:
    DynamicArray() : capacity(4), current_size(0) { data = new T[capacity]; }
    ~DynamicArray() { delete[] data; }
    void push_back(const T& value) {
        if (current_size == capacity) resize(capacity * 2);
        data[current_size++] = value;
    }
    T& operator[](size_t index) {
        if (index >= current_size) throw std::out_of_range("Index out of bounds");
        return data[index];
    }
    const T& operator[](size_t index) const {
        if (index >= current_size) throw std::out_of_range("Index out of bounds");
        return data[index];
    }
    size_t size() const { return current_size; }
    void clear() { current_size = 0; }
};
#endif