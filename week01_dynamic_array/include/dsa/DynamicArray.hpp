//
// Created by marius on 1/26/26.
//

// Supported by GCC, Clang, MSVC

// DynamicArray<T>
// ----------------
// A simple resizable array implementation.
// Implemented as a template so it can store elements of any type T.
// Used to demonstrate memory allocation, resizing, and basic container design.
// This is an educational implementation (not a replacement for std::vector).

#pragma once
#include <cstddef>
#include <stdexcept>

namespace dsa {

    template <class T>
    class DynamicArray {
    public:
        DynamicArray();
        ~DynamicArray();

        std::size_t size() const;
        std::size_t capacity() const;

        T& operator[](std::size_t index);
        const T& operator[](std::size_t index) const;

        // Safe access
        T& at(std::size_t index);
        const T& at(std::size_t index) const;

        void push_back(const T& value);
        void pop_back();

        // Part B (lab / homework)
        void insert(std::size_t index, const T& value) {
            // TODO INSERT
        }
        void erase(std::size_t index);

        void reserve(std::size_t newCapacity);

    private:
        T* data_;
        std::size_t size_;
        std::size_t capacity_;
    };

} // namespace dsa
