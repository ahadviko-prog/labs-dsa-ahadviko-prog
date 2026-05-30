#pragma once

#include <cstddef>
#include <stdexcept>

namespace dsa {

template <class T>
class SinglyLinkedList {
private:
    struct Node {
        T value;
        Node* next;

        Node(const T& v, Node* n = nullptr)
            : value(v), next(n) {}
    };

    Node* head_;
    std::size_t size_;

public:
    SinglyLinkedList()
        : head_(nullptr), size_(0) {}

    ~SinglyLinkedList() {
        clear();
    }

    SinglyLinkedList(const SinglyLinkedList&) = delete;
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;

    bool empty() const {
        return size_ == 0;
    }

    std::size_t size() const {
        return size_;
    }

    T& front() {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return head_->value;
    }

    const T& front() const {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return head_->value;
    }

    T& back() {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }

        Node* current = head_;
        while (current->next != nullptr) {
            current = current->next;
        }

        return current->value;
    }

    const T& back() const {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }

        Node* current = head_;
        while (current->next != nullptr) {
            current = current->next;
        }

        return current->value;
    }

    void push_front(const T& value) {
        head_ = new Node(value, head_);
        ++size_;
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value);

        if (empty()) {
            head_ = newNode;
        } else {
            Node* current = head_;

            while (current->next != nullptr) {
                current = current->next;
            }

            current->next = newNode;
        }

        ++size_;
    }

    T pop_front() {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }

        T value = head_->value;
        Node* temp = head_;

        head_ = head_->next;
        delete temp;
        --size_;

        return value;
    }

    void pop_back() {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }

        if (head_->next == nullptr) {
            delete head_;
            head_ = nullptr;
            size_ = 0;
            return;
        }

        Node* current = head_;

        while (current->next->next != nullptr) {
            current = current->next;
        }

        delete current->next;
        current->next = nullptr;
        --size_;
    }

    bool find(const T& value) const {
        Node* current = head_;

        while (current != nullptr) {
            if (current->value == value) {
                return true;
            }

            current = current->next;
        }

        return false;
    }

    bool remove_first(const T& value) {
        if (empty()) {
            return false;
        }

        if (head_->value == value) {
            Node* temp = head_;
            head_ = head_->next;

            delete temp;
            --size_;

            return true;
        }

        Node* current = head_;

        while (current->next != nullptr &&
               current->next->value != value) {
            current = current->next;
        }

        if (current->next == nullptr) {
            return false;
        }

        Node* temp = current->next;
        current->next = temp->next;

        delete temp;
        --size_;

        return true;
    }

    void reverse() {
        Node* prev = nullptr;
        Node* current = head_;

        while (current != nullptr) {
            Node* next = current->next;

            current->next = prev;
            prev = current;
            current = next;
        }

        head_ = prev;
    }

    void clear() {
        while (head_ != nullptr) {
            Node* temp = head_;
            head_ = head_->next;

            delete temp;
        }

        size_ = 0;
    }
};

} // namespace dsa