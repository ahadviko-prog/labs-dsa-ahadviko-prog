#pragma once

#include <cstddef>
#include <stdexcept>

namespace dsa {

    template <class T>
    class Deque {
    public:
        Deque()
            : data_(new T[4]),
              capacity_(4),
              front_(0),
              size_(0) {
        }

        ~Deque() {
            delete[] data_;
        }

        void push_front(const T& value) {
            if (size_ == capacity_) {
                resize(capacity_ * 2);
            }

            front_ = (front_ + capacity_ - 1) % capacity_;
            data_[front_] = value;
            ++size_;
        }

        void push_back(const T& value) {
            if (size_ == capacity_) {
                resize(capacity_ * 2);
            }

            std::size_t backIndex = (front_ + size_) % capacity_;
            data_[backIndex] = value;
            ++size_;
        }

        void pop_front() {
            if (empty()) {
                throw std::out_of_range("Deque is empty");
            }

            front_ = (front_ + 1) % capacity_;
            --size_;
        }

        void pop_back() {
            if (empty()) {
                throw std::out_of_range("Deque is empty");
            }

            --size_;
        }

        T& front() {
            if (empty()) {
                throw std::out_of_range("Deque is empty");
            }

            return data_[front_];
        }

        T& back() {
            if (empty()) {
                throw std::out_of_range("Deque is empty");
            }

            std::size_t backIndex = (front_ + size_ - 1) % capacity_;
            return data_[backIndex];
        }

        bool empty() const {
            return size_ == 0;
        }

        std::size_t size() const {
            return size_;
        }

    private:
        T* data_;
        std::size_t capacity_;
        std::size_t front_;
        std::size_t size_;

        void resize(std::size_t newCapacity) {
            T* newData = new T[newCapacity];

            for (std::size_t i = 0; i < size_; ++i) {
                newData[i] = data_[(front_ + i) % capacity_];
            }

            delete[] data_;

            data_ = newData;
            capacity_ = newCapacity;
            front_ = 0;
        }
    };

}