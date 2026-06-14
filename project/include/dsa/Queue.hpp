#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <stdexcept>

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };
    Node* frontNode;
    Node* rearNode;
    size_t count;
public:
    Queue() : frontNode(nullptr), rearNode(nullptr), count(0) {}
    ~Queue() { while (!isEmpty()) dequeue(); }
    void enqueue(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) { frontNode = rearNode = newNode; }
        else { rearNode->next = newNode; rearNode = newNode; }
        count++;
    }
    void dequeue() {
        if (isEmpty()) throw std::underflow_error("Queue underflow");
        Node* temp = frontNode;
        frontNode = frontNode->next;
        delete temp;
        if (frontNode == nullptr) rearNode = nullptr;
        count--;
    }
    T front() const {
        if (isEmpty()) throw std::underflow_error("Queue is empty");
        return frontNode->data;
    }
    bool isEmpty() const { return frontNode == nullptr; }
    size_t size() const { return count; }
};
#endif