#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP
#include <iostream>

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };
    Node* head;
    size_t count;
public:
    LinkedList() : head(nullptr), count(0) {}
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
    void append(const T& value) {
        Node* newNode = new Node(value);
        if (!head) { head = newNode; }
        else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
        count++;
    }
    void display() const {
        Node* temp = head;
        while (temp) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "nullptr\n";
    }
    size_t size() const { return count; }
};
#endif