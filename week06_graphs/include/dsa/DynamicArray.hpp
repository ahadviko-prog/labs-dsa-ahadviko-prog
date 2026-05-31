#pragma once

#include <stdexcept>

namespace dsa {

    template <typename T>
    class DynamicArray {
    private:
        T* data_;
        int size_;
        int capacity_;

        void resize(int newCapacity) {
            T* newData = new T[newCapacity];

            for (int i = 0; i < size_; i++) {
                newData[i] = data_[i];
            }

            delete[] data_;
            data_ = newData;
            capacity_ = newCapacity;
        }

    public:
        DynamicArray()
            : data_(nullptr), size_(0), capacity_(0) {}

        ~DynamicArray() {
            delete[] data_;
        }

        DynamicArray(const DynamicArray& other)
            : size_(other.size_), capacity_(other.capacity_) {

            data_ = new T[capacity_];

            for (int i = 0; i < size_; i++) {
                data_[i] = other.data_[i];
            }
        }

        DynamicArray& operator=(const DynamicArray& other) {
            if (this != &other) {
                delete[] data_;

                size_ = other.size_;
                capacity_ = other.capacity_;

                data_ = new T[capacity_];

                for (int i = 0; i < size_; i++) {
                    data_[i] = other.data_[i];
                }
            }

            return *this;
        }

        void push_back(const T& value) {
            if (size_ == capacity_) {
                resize(capacity_ == 0 ? 1 : capacity_ * 2);
            }

            data_[size_++] = value;
        }

        int size() const {
            return size_;
        }

        T& operator[](int index) {
            return data_[index];
        }

        const T& operator[](int index) const {
            return data_[index];
        }
    };

}