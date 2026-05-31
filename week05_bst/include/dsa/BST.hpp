//
// Created by marius on 2/19/26.
//

#pragma once

#include <cstddef>
#include <stdexcept>

namespace dsa {

template <class T>
class BST {
private:
    struct Node {
        T key;
        Node* left;
        Node* right;

        Node(const T& k)
            : key(k), left(nullptr), right(nullptr) {}
    };

public:
    BST();
    ~BST();

    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    bool empty() const;
    std::size_t size() const;

    bool contains(const T& key) const;

    // Insert: ignore duplicates
    void insert(const T& key);

    // Remove: returns true if removed
    bool remove(const T& key);

    const T& min() const;
    const T& max() const;

    void inorder(T* out) const;

    std::size_t height() const;

    void clear();

private:
    Node* insert(Node* node, const T& key, bool& inserted);
    bool contains(Node* node, const T& key) const;

    Node* remove(Node* node, const T& key, bool& removed);
    Node* find_min_node(Node* node) const;

    const T& min(Node* node) const;
    const T& max(Node* node) const;

    void inorder(Node* node, T* out, std::size_t& idx) const;

    std::size_t height(Node* node) const;
    void clear(Node* node);

private:
    Node* root_;
    std::size_t size_;
};

// ======================
// IMPLEMENTATION
// ======================

template <class T>
BST<T>::BST()
    : root_(nullptr), size_(0) {}

template <class T>
BST<T>::~BST() {
    clear();
}

template <class T>
bool BST<T>::empty() const {
    return size_ == 0;
}

template <class T>
std::size_t BST<T>::size() const {
    return size_;
}

template <class T>
bool BST<T>::contains(const T& key) const {
    return contains(root_, key);
}

template <class T>
bool BST<T>::contains(Node* node, const T& key) const {
    if (node == nullptr)
        return false;

    if (key == node->key)
        return true;

    if (key < node->key)
        return contains(node->left, key);

    return contains(node->right, key);
}

template <class T>
void BST<T>::insert(const T& key) {
    bool inserted = false;
    root_ = insert(root_, key, inserted);

    if (inserted)
        ++size_;
}

template <class T>
typename BST<T>::Node* BST<T>::insert(
    Node* node,
    const T& key,
    bool& inserted) {

    if (node == nullptr) {
        inserted = true;
        return new Node(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key, inserted);
    }
    else if (key > node->key) {
        node->right = insert(node->right, key, inserted);
    }

    return node;
}

template <class T>
const T& BST<T>::min() const {
    if (empty())
        throw std::out_of_range("BST empty");

    return min(root_);
}

template <class T>
const T& BST<T>::min(Node* node) const {
    if (node->left == nullptr)
        return node->key;

    return min(node->left);
}

template <class T>
const T& BST<T>::max() const {
    if (empty())
        throw std::out_of_range("BST empty");

    return max(root_);
}

template <class T>
const T& BST<T>::max(Node* node) const {
    if (node->right == nullptr)
        return node->key;

    return max(node->right);
}

template <class T>
void BST<T>::inorder(T* out) const {
    std::size_t idx = 0;
    inorder(root_, out, idx);
}

template <class T>
void BST<T>::inorder(
    Node* node,
    T* out,
    std::size_t& idx) const {

    if (node == nullptr)
        return;

    inorder(node->left, out, idx);
    out[idx++] = node->key;
    inorder(node->right, out, idx);
}

template <class T>
std::size_t BST<T>::height() const {
    return height(root_);
}

template <class T>
std::size_t BST<T>::height(Node* node) const {
    if (node == nullptr)
        return 0;

    std::size_t left = height(node->left);
    std::size_t right = height(node->right);

    return 1 + (left > right ? left : right);
}

template <class T>
typename BST<T>::Node* BST<T>::find_min_node(Node* node) const {
    while (node->left != nullptr)
        node = node->left;

    return node;
}

template <class T>
bool BST<T>::remove(const T& key) {
    bool removed = false;
    root_ = remove(root_, key, removed);

    if (removed)
        --size_;

    return removed;
}

template <class T>
typename BST<T>::Node* BST<T>::remove(
    Node* node,
    const T& key,
    bool& removed) {

    if (node == nullptr)
        return nullptr;

    if (key < node->key) {
        node->left = remove(node->left, key, removed);
    }
    else if (key > node->key) {
        node->right = remove(node->right, key, removed);
    }
    else {
        removed = true;

        // no children
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }

        // one child
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }

        if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        // two children
        Node* successor = find_min_node(node->right);
        node->key = successor->key;

        bool dummy = false;
        node->right = remove(node->right, successor->key, dummy);
    }

    return node;
}

template <class T>
void BST<T>::clear() {
    clear(root_);
    root_ = nullptr;
    size_ = 0;
}

template <class T>
void BST<T>::clear(Node* node) {
    if (node == nullptr)
        return;

    clear(node->left);
    clear(node->right);

    delete node;
}

} // namespace dsa