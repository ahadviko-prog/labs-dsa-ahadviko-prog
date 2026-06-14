#pragma once

#include <stdexcept>

namespace dsa {

    template <typename T>
    class Queue {
    private:
        struct Node {
            T data;
            Node* next;

            Node(const T& value)
                : data(value), next(nullptr) {}
        };

        Node* front_;
        Node* rear_;

    public:
        Queue()
            : front_(nullptr), rear_(nullptr) {}

        ~Queue() {
            while (!empty()) {
                dequeue();
            }
        }

        bool empty() const {
            return front_ == nullptr;
        }

        void enqueue(const T& value) {
            Node* node = new Node(value);

            if (rear_ == nullptr) {
                front_ = rear_ = node;
            } else {
                rear_->next = node;
                rear_ = node;
            }
        }

        void dequeue() {
            if (empty()) {
                throw std::out_of_range("Queue empty");
            }

            Node* temp = front_;
            front_ = front_->next;

            if (front_ == nullptr) {
                rear_ = nullptr;
            }

            delete temp;
        }

        T& front() {
            if (empty()) {
                throw std::out_of_range("Queue empty");
            }

            return front_->data;
        }

        const T& front() const {
            if (empty()) {
                throw std::out_of_range("Queue empty");
            }

            return front_->data;
        }
    };

}