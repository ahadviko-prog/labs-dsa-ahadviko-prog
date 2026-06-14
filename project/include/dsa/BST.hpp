#ifndef BST_HPP
#define BST_HPP

template <typename T>
class BST {
public:
    struct TreeNode {
        T data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(const T& val) : data(val), left(nullptr), right(nullptr) {}
    };
private:
    TreeNode* root;
    TreeNode* insert(TreeNode* node, const T& value) {
        if (!node) return new TreeNode(value);
        if (value < node->data) node->left = insert(node->left, value);
        else node->right = insert(node->right, value);
        return node;
    }
    void destroyTree(TreeNode* node) {
        if (!node) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
public:
    BST() : root(nullptr) {}
    ~BST() { destroyTree(root); }
    void insert(const T& value) { root = insert(root, value); }
    TreeNode* getRoot() const { return root; }
};
#endif