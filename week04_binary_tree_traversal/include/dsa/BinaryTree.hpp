#pragma once
#include <cstddef>
#include <stdexcept>

namespace dsa {

template <class T>
class BinaryTree {
private:
    struct Node {
        T value;
        Node* left;
        Node* right;

        Node(const T& v)
            : value(v), left(nullptr), right(nullptr) {}
    };

public:
    BinaryTree();
    ~BinaryTree();

    BinaryTree(const BinaryTree&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;

    bool empty() const;
    std::size_t size() const;

    void set_root(const T& value);
    void add_left(const T& parentValue, const T& childValue);
    void add_right(const T& parentValue, const T& childValue);

    void preorder(T* out) const;
    void inorder(T* out) const;
    void postorder(T* out) const;

    std::size_t height() const;
    bool contains(const T& value) const;

    void clear();

private:
    Node* find(Node* node, const T& value) const;

    void preorder(Node* node, T* out, std::size_t& idx) const;
    void inorder(Node* node, T* out, std::size_t& idx) const;
    void postorder(Node* node, T* out, std::size_t& idx) const;

    std::size_t height(Node* node) const;
    bool contains(Node* node, const T& value) const;

    void clear(Node* node);

private:
    Node* root_;
    std::size_t size_;
};

// =========================
// Constructor / Destructor
// =========================

template <class T>
BinaryTree<T>::BinaryTree()
    : root_(nullptr), size_(0) {}

template <class T>
BinaryTree<T>::~BinaryTree() {
    clear();
}

// =========================
// Basic Operations
// =========================

template <class T>
bool BinaryTree<T>::empty() const {
    return size_ == 0;
}

template <class T>
std::size_t BinaryTree<T>::size() const {
    return size_;
}

// =========================
// Build Tree
// =========================

template <class T>
void BinaryTree<T>::set_root(const T& value) {
    if (root_ != nullptr) {
        throw std::logic_error("root already exists");
    }

    root_ = new Node(value);
    size_ = 1;
}

template <class T>
void BinaryTree<T>::add_left(const T& parentValue, const T& childValue) {
    Node* parent = find(root_, parentValue);

    if (parent == nullptr) {
        throw std::out_of_range("parent not found");
    }

    if (parent->left != nullptr) {
        throw std::logic_error("left child already exists");
    }

    parent->left = new Node(childValue);
    ++size_;
}

template <class T>
void BinaryTree<T>::add_right(const T& parentValue, const T& childValue) {
    Node* parent = find(root_, parentValue);

    if (parent == nullptr) {
        throw std::out_of_range("parent not found");
    }

    if (parent->right != nullptr) {
        throw std::logic_error("right child already exists");
    }

    parent->right = new Node(childValue);
    ++size_;
}

// =========================
// Find Helper
// =========================

template <class T>
typename BinaryTree<T>::Node*
BinaryTree<T>::find(Node* node, const T& value) const {
    if (node == nullptr) {
        return nullptr;
    }

    if (node->value == value) {
        return node;
    }

    Node* found = find(node->left, value);
    if (found != nullptr) {
        return found;
    }

    return find(node->right, value);
}

// =========================
// Traversals
// =========================

template <class T>
void BinaryTree<T>::preorder(T* out) const {
    std::size_t idx = 0;
    preorder(root_, out, idx);
}

template <class T>
void BinaryTree<T>::inorder(T* out) const {
    std::size_t idx = 0;
    inorder(root_, out, idx);
}

template <class T>
void BinaryTree<T>::postorder(T* out) const {
    std::size_t idx = 0;
    postorder(root_, out, idx);
}

template <class T>
void BinaryTree<T>::preorder(Node* node, T* out, std::size_t& idx) const {
    if (node == nullptr) {
        return;
    }

    out[idx++] = node->value;
    preorder(node->left, out, idx);
    preorder(node->right, out, idx);
}

template <class T>
void BinaryTree<T>::inorder(Node* node, T* out, std::size_t& idx) const {
    if (node == nullptr) {
        return;
    }

    inorder(node->left, out, idx);
    out[idx++] = node->value;
    inorder(node->right, out, idx);
}

template <class T>
void BinaryTree<T>::postorder(Node* node, T* out, std::size_t& idx) const {
    if (node == nullptr) {
        return;
    }

    postorder(node->left, out, idx);
    postorder(node->right, out, idx);
    out[idx++] = node->value;
}

// =========================
// Height
// =========================

template <class T>
std::size_t BinaryTree<T>::height() const {
    return height(root_);
}

template <class T>
std::size_t BinaryTree<T>::height(Node* node) const {
    if (node == nullptr) {
        return 0;
    }

    std::size_t leftHeight = height(node->left);
    std::size_t rightHeight = height(node->right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// =========================
// Contains
// =========================

template <class T>
bool BinaryTree<T>::contains(const T& value) const {
    return contains(root_, value);
}

template <class T>
bool BinaryTree<T>::contains(Node* node, const T& value) const {
    if (node == nullptr) {
        return false;
    }

    if (node->value == value) {
        return true;
    }

    return contains(node->left, value) ||
           contains(node->right, value);
}

// =========================
// Clear / Memory Management
// =========================

template <class T>
void BinaryTree<T>::clear() {
    clear(root_);
    root_ = nullptr;
    size_ = 0;
}

template <class T>
void BinaryTree<T>::clear(Node* node) {
    if (node == nullptr) {
        return;
    }

    clear(node->left);
    clear(node->right);

    delete node;
}

} // namespace dsa