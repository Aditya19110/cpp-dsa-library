#pragma once

#include <memory>
#include <functional>
#include <algorithm>
#include <queue>

namespace DSA {

/**
 * @brief Self-balancing AVL Tree implementation
 * 
 * Time Complexities (guaranteed):
 * - Search: O(log n)
 * - Insert: O(log n)
 * - Delete: O(log n)
 * 
 * Space Complexity: O(n)
 */
template<typename T>
class AVLTree {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        int height;
        
        explicit Node(const T& value) 
            : data(value), left(nullptr), right(nullptr), height(0) {}
        explicit Node(T&& value) 
            : data(std::move(value)), left(nullptr), right(nullptr), height(0) {}
    };
    
    std::unique_ptr<Node> root_;
    size_t size_;
    
    // Get height of node
    int height(const Node* node) const {
        return node ? node->height : -1;
    }
    
    // Update height of node
    void updateHeight(Node* node) {
        if (node) {
            node->height = 1 + std::max(height(node->left.get()), 
                                       height(node->right.get()));
        }
    }
    
    // Get balance factor
    int getBalance(const Node* node) const {
        return node ? height(node->left.get()) - height(node->right.get()) : 0;
    }
    
    // Right rotation
    std::unique_ptr<Node> rotateRight(std::unique_ptr<Node> y) {
        auto x = std::move(y->left);
        y->left = std::move(x->right);
        
        updateHeight(y.get());
        x->right = std::move(y);
        updateHeight(x.get());
        
        return x;
    }
    
    // Left rotation
    std::unique_ptr<Node> rotateLeft(std::unique_ptr<Node> x) {
        auto y = std::move(x->right);
        x->right = std::move(y->left);
        
        updateHeight(x.get());
        y->left = std::move(x);
        updateHeight(y.get());
        
        return y;
    }
    
    // Balance the tree
    std::unique_ptr<Node> balance(std::unique_ptr<Node> node) {
        updateHeight(node.get());
        int balanceFactor = getBalance(node.get());
        
        // Left-Left case
        if (balanceFactor > 1 && getBalance(node->left.get()) >= 0) {
            return rotateRight(std::move(node));
        }
        
        // Left-Right case
        if (balanceFactor > 1 && getBalance(node->left.get()) < 0) {
            node->left = rotateLeft(std::move(node->left));
            return rotateRight(std::move(node));
        }
        
        // Right-Right case
        if (balanceFactor < -1 && getBalance(node->right.get()) <= 0) {
            return rotateLeft(std::move(node));
        }
        
        // Right-Left case
        if (balanceFactor < -1 && getBalance(node->right.get()) > 0) {
            node->right = rotateRight(std::move(node->right));
            return rotateLeft(std::move(node));
        }
        
        return node;
    }
    
    // Insert helper
    std::unique_ptr<Node> insertHelper(std::unique_ptr<Node> node, const T& value) {
        if (!node) {
            ++size_;
            return std::make_unique<Node>(value);
        }
        
        if (value < node->data) {
            node->left = insertHelper(std::move(node->left), value);
        } else if (value > node->data) {
            node->right = insertHelper(std::move(node->right), value);
        } else {
            return node; // Duplicates not allowed
        }
        
        return balance(std::move(node));
    }
    
    // Find minimum node
    Node* findMin(Node* node) const {
        while (node && node->left) {
            node = node->left.get();
        }
        return node;
    }
    
    // Remove helper
    std::unique_ptr<Node> removeHelper(std::unique_ptr<Node> node, const T& value) {
        if (!node) return nullptr;
        
        if (value < node->data) {
            node->left = removeHelper(std::move(node->left), value);
        } else if (value > node->data) {
            node->right = removeHelper(std::move(node->right), value);
        } else {
            // Node found
            if (!node->left || !node->right) {
                --size_;
                return node->left ? std::move(node->left) : std::move(node->right);
            }
            
            // Node has two children
            Node* minNode = findMin(node->right.get());
            node->data = minNode->data;
            node->right = removeHelper(std::move(node->right), minNode->data);
        }
        
        return balance(std::move(node));
    }
    
    // Search helper
    bool searchHelper(const Node* node, const T& value) const {
        if (!node) return false;
        
        if (value == node->data) return true;
        if (value < node->data) return searchHelper(node->left.get(), value);
        return searchHelper(node->right.get(), value);
    }
    
    // In-order traversal helper
    void inOrderHelper(const Node* node, std::function<void(const T&)> visit) const {
        if (!node) return;
        inOrderHelper(node->left.get(), visit);
        visit(node->data);
        inOrderHelper(node->right.get(), visit);
    }

public:
    AVLTree() : root_(nullptr), size_(0) {}
    
    // Move constructor
    AVLTree(AVLTree&& other) noexcept
        : root_(std::move(other.root_)), size_(other.size_) {
        other.size_ = 0;
    }
    
    // Move assignment
    AVLTree& operator=(AVLTree&& other) noexcept {
        if (this != &other) {
            root_ = std::move(other.root_);
            size_ = other.size_;
            other.size_ = 0;
        }
        return *this;
    }
    
    // Delete copy operations
    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;
    
    // Insert value - O(log n) guaranteed
    void insert(const T& value) {
        root_ = insertHelper(std::move(root_), value);
    }
    
    void insert(T&& value) {
        root_ = insertHelper(std::move(root_), std::move(value));
    }
    
    // Remove value - O(log n) guaranteed
    void remove(const T& value) {
        root_ = removeHelper(std::move(root_), value);
    }
    
    // Search for value - O(log n) guaranteed
    bool search(const T& value) const {
        return searchHelper(root_.get(), value);
    }
    
    // In-order traversal
    void inOrder(std::function<void(const T&)> visit) const {
        inOrderHelper(root_.get(), visit);
    }
    
    // Utility functions
    bool empty() const noexcept { return root_ == nullptr; }
    size_t size() const noexcept { return size_; }
    int height() const { return height(root_.get()); }
    
    void clear() {
        root_.reset();
        size_ = 0;
    }
};

} // namespace DSA
