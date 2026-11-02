#include "project/binary_search_tree.h"

#include <algorithm>
#include <stdexcept>

BinarySearchTree::BinarySearchTree() : root_(nullptr), size_(0) {}

BinarySearchTree::~BinarySearchTree() {
    deleteSubtree(root_);
}

void BinarySearchTree::deleteSubtree(TreeNode* node) {
    if (node == nullptr) {
        return;
    }

    deleteSubtree(node->left);
    deleteSubtree(node->right);
    delete node;
}

bool BinarySearchTree::insert(int value) {
    (void)value;
    const std::size_t sizeBefore = size_;
    root_ = insertRecursive(root_, value);
    return size_ != sizeBefore;
}

bool BinarySearchTree::remove(int value) {
    (void)value;
    const std::size_t sizeBefore = size_;
    root_ = removeRecursive(root_, value);
    return size_ != sizeBefore;
}

bool BinarySearchTree::search(int value) const {
    (void)value;
    return searchRecursive(root_, value);
}

bool BinarySearchTree::contains(int value) const {
    (void)value;
    return search(value);
}

bool BinarySearchTree::empty() const noexcept {
    return size_ == 0;
}

std::size_t BinarySearchTree::size() const noexcept {
    return size_;
}

int BinarySearchTree::height() const {
    return heightRecursive(root_);
}

std::vector<int> BinarySearchTree::inorderTraversal() const {
    std::vector<int> result;
    inorderRecursive(root_, result);
    return result;
}

std::vector<int> BinarySearchTree::preorderTraversal() const {
    std::vector<int> result;
    preorderRecursive(root_, result);
    return result;
}

std::vector<int> BinarySearchTree::postorderTraversal() const {
    std::vector<int> result;
    postorderRecursive(root_, result);
    return result;
}

int BinarySearchTree::minimum() const {
    if (empty()) {
        throw std::logic_error("BST is empty");
    }
    return minimumRecursive(root_);
}

int BinarySearchTree::maximum() const {
    if (empty()) {
        throw std::logic_error("BST is empty");
    }
    return maximumRecursive(root_);
}

TreeNode* BinarySearchTree::insertRecursive(TreeNode* node, int value) {
    (void)node;
    (void)value;
    // base case: find empty spot where new value belongs
    if (node == nullptr) {
        ++size_;
        return new TreeNode(value);
    }
    // small values left, larger right; equal values ignored
    if (value < node->value) {
        node->left = insertRecursive(node->left, value);
    } else if (value > node->value) {
        node->right = insertRecursive(node->right, value);
    }
    return node;
}

TreeNode* BinarySearchTree::removeRecursive(TreeNode* node, int value) {
    (void)node;
    (void)value;
    // base case = value not found
    if (node == nullptr) {
        return nullptr;
    }
    if (value < node->value) {
        node->left = removeRecursive(node->left, value);
    } else if (value > node->value) {
        node->right = removeRecursive(node->right, value);
    } else {
        if (node->left == nullptr) {
            TreeNode* rightChild = node->right;
            delete node;
            --size_;
            return rightChild;
        }
        if (node->right == nullptr) {
            TreeNode* leftChild = node->left;
            delete node;
            --size_;
            return leftChild;
        }
        const int successorValue = minimumRecursive(node->right);
        node->value = successorValue;
        node->right = removeRecursive(node->right, successorValue);
    }
    return node;
}

bool BinarySearchTree::searchRecursive(const TreeNode* node, int value) const {
    (void)node;
    (void)value;
    if (node == nullptr) {
        return false;
    }
    if (value == node->value) {
        return true;
    }
    return value < node->value ? searchRecursive(node->left, value)
                               : searchRecursive(node->right, value);
}

void BinarySearchTree::inorderRecursive(const TreeNode* node, std::vector<int>& result) const {
    (void)node;
    (void)result;
    // left > node > right
    if (node == nullptr) {
        return;
    }
    inorderRecursive(node->left, result);
    result.push_back(node->value);
    inorderRecursive(node->right, result);
}

void BinarySearchTree::preorderRecursive(const TreeNode* node, std::vector<int>& result) const {
    (void)node;
    (void)result;
    // node > left > right.
    if (node == nullptr) {
        return;
    }
    result.push_back(node->value);
    preorderRecursive(node->left, result);
    preorderRecursive(node->right, result);
}

void BinarySearchTree::postorderRecursive(const TreeNode* node, std::vector<int>& result) const {
    (void)node;
    (void)result;
    // left > right > node
    if (node == nullptr) {
        return;
    }
    postorderRecursive(node->left, result);
    postorderRecursive(node->right, result);
    result.push_back(node->value);
}

int BinarySearchTree::heightRecursive(const TreeNode* node) const {
    (void)node;
    // empty subtree has height -1; single node has height 0
    if (node == nullptr) {
        return 0;
    }
    return std::max(heightRecursive(node->left), heightRecursive(node->right)) + 1;
}

int BinarySearchTree::minimumRecursive(const TreeNode* node) const {
    (void)node;
    // min is leftmost node
    if (node->left == nullptr) {
        return node->value;
    }
    return minimumRecursive(node->left);
}

int BinarySearchTree::maximumRecursive(const TreeNode* node) const {
    (void)node;
    // max is rightmost node
    if (node->right == nullptr) {
        return node->value;
    }
    return maximumRecursive(node->right);
}