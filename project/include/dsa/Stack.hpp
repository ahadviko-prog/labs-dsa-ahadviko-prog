#ifndef STACK_HPP
#define STACK_HPP
#include <stdexcept>

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };
    Node* topNode;
    size_t count;
public:
    Stack() : topNode(nullptr), count(0) {}
    ~Stack() { while (!isEmpty()) pop(); }
    void push(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
        count++;
    }
    void pop() {
        if (isEmpty()) throw std::underflow_error("Stack underflow");
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        count--;
    }
    T top() const {
        if (isEmpty()) throw std::underflow_error("Stack is empty");
        return topNode->data;
    }
    bool isEmpty() const { return topNode == nullptr; }
    size_t size() const { return count; }
};
#endif