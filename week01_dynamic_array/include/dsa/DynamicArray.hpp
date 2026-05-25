//
// Created by marius on 1/26/26.
//

#pragma once

#include <cstddef>
#include <stdexcept>

namespace dsa {

template <class T>
class DynamicArray {
public:
    // Constructor
    DynamicArray()
        : data_(nullptr), size_(0), capacity_(0) {}

    // Destructor
    ~DynamicArray() {
        delete[] data_;
    }

    // Current number of elements
    std::size_t size() const {
        return size_;
    }

    // Current allocated capacity
    std::size_t capacity() const {
        return capacity_;
    }

    // Access without bounds checking
    T& operator[](std::size_t index) {
        return data_[index];
    }

    const T& operator[](std::size_t index) const {
        return data_[index];
    }

    // Safe access with bounds checking
    T& at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    const T& at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    // Reserve memory
    void reserve(std::size_t newCapacity) {
        // Do not shrink
        if (newCapacity <= capacity_) {
            return;
        }

        // Allocate new memory
        T* newData = new T[newCapacity];

        // Copy old elements
        for (std::size_t i = 0; i < size_; ++i) {
            newData[i] = data_[i];
        }

        // Free old memory
        delete[] data_;

        // Update pointers and capacity
        data_ = newData;
        capacity_ = newCapacity;
    }

    // Add element to the end
    void push_back(const T& value) {
        // Resize if needed
        if (size_ >= capacity_) {
            std::size_t newCapacity =
                (capacity_ == 0) ? 1 : capacity_ * 2;

            reserve(newCapacity);
        }

        data_[size_] = value;
        ++size_;
    }

    // Remove last element
    void pop_back() {
        if (size_ > 0) {
            --size_;
        }
    }

    // Insert element at index
    void insert(std::size_t index, const T& value) {
        // Valid: 0 <= index <= size
        if (index > size_) {
            throw std::out_of_range("Index out of range");
        }

        // Resize if needed
        if (size_ >= capacity_) {
            std::size_t newCapacity =
                (capacity_ == 0) ? 1 : capacity_ * 2;

            reserve(newCapacity);
        }

        // Shift elements right
        for (std::size_t i = size_; i > index; --i) {
            data_[i] = data_[i - 1];
        }

        // Insert value
        data_[index] = value;

        ++size_;
    }

    // Erase element at index
    void erase(std::size_t index) {
        // Valid: 0 <= index < size
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }

        // Shift elements left
        for (std::size_t i = index; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }

        --size_;
    }

private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;
};

} // namespace dsa