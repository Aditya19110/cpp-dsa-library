#pragma once

#include <memory>
#include <functional>
#include <stdexcept>
#include <queue>

namespace DSA {

/**
 * @brief Binary Search Tree implementation
 * 
 * Time Complexities (average case):
 * - Search: O(log n)
 * - Insert: O(log n)
 * - Delete: O(log n)
 * 
 * Time Complexities (worst case - skewed tree):
 * - Search: O(n)
 * - Insert: O(n)
 * - Delete: O(n)
 * 
 * Space Complexity: O(n)
 */
template<typename T>
class BST {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        
        explicit Node(const T& value) 
            : data(value), left(nullptr), right(nullptr) {}
        explicit Node(T&& value) 
            : data(std::move(value)), left(nullptr), right(nullptr) {}
    };
    
    std::unique_ptr<Node> root_;
    size_t size_;
    
    // Helper function for insertion
    void insertHelper(std::unique_ptr<Node>& node, const T& value) {
        if (!node) {
            node = std::make_unique<Node>(value);
            ++size_;
            return;
        }
        
        if (value < node->data) {
            insertHelper(node->left, value);
        } else if (value > node->data) {
            insertHelper(node->right, value);
        }
        // Duplicates are ignored
    }
    
    // Helper function for search
    bool searchHelper(const Node* node, const T& value) const {
        if (!node) return false;
        
        if (value == node->data) return true;
        if (value < node->data) return searchHelper(node->left.get(), value);
        return searchHelper(node->right.get(), value);
    }
    
    // Helper function for finding minimum
    Node* findMin(Node* node) const {
        while (node && node->left) {
            node = node->left.get();
        }
        return node;
    }
    
    // Helper function for deletion
    std::unique_ptr<Node> removeHelper(std::unique_ptr<Node> node, const T& value) {
        if (!node) return nullptr;
        
        if (value < node->data) {
            node->left = removeHelper(std::move(node->left), value);
        } else if (value > node->data) {
            node->right = removeHelper(std::move(node->right), value);
        } else {
            // Node found
            if (!node->left) {
                --size_;
                return std::move(node->right);
            }
            if (!node->right) {
                --size_;
                return std::move(node->left);
            }
            
            // Node has two children
            Node* minNode = findMin(node->right.get());
            node->data = minNode->data;
            node->right = removeHelper(std::move(node->right), minNode->data);
        }
        
        return node;
    }
    
    // In-order traversal helper
    void inOrderHelper(const Node* node, std::function<void(const T&)> visit) const {
        if (!node) return;
        inOrderHelper(node->left.get(), visit);
        visit(node->data);
        inOrderHelper(node->right.get(), visit);
    }
    
    // Pre-order traversal helper
    void preOrderHelper(const Node* node, std::function<void(const T&)> visit) const {
        if (!node) return;
        visit(node->data);
        preOrderHelper(node->left.get(), visit);
        preOrderHelper(node->right.get(), visit);
    }
    
    // Post-order traversal helper
    void postOrderHelper(const Node* node, std::function<void(const T&)> visit) const {
        if (!node) return;
        postOrderHelper(node->left.get(), visit);
        postOrderHelper(node->right.get(), visit);
        visit(node->data);
    }
    
    // Height helper
    int heightHelper(const Node* node) const {
        if (!node) return -1;
        return 1 + std::max(heightHelper(node->left.get()), 
                           heightHelper(node->right.get()));
    }

public:
    BST() : root_(nullptr), size_(0) {}
    
    // Move constructor
    BST(BST&& other) noexcept
        : root_(std::move(other.root_)), size_(other.size_) {
        other.size_ = 0;
    }
    
    // Move assignment
    BST& operator=(BST&& other) noexcept {
        if (this != &other) {
            root_ = std::move(other.root_);
            size_ = other.size_;
            other.size_ = 0;
        }
        return *this;
    }
    
    // Delete copy operations
    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;
    
    // Insert value - O(log n) average, O(n) worst
    void insert(const T& value) {
        insertHelper(root_, value);
    }
    
    void insert(T&& value) {
        insertHelper(root_, std::move(value));
    }
    
    // Search for value - O(log n) average, O(n) worst
    bool search(const T& value) const {
        return searchHelper(root_.get(), value);
    }
    
    // Remove value - O(log n) average, O(n) worst
    void remove(const T& value) {
        root_ = removeHelper(std::move(root_), value);
    }
    
    // Traversals
    void inOrder(std::function<void(const T&)> visit) const {
        inOrderHelper(root_.get(), visit);
    }
    
    void preOrder(std::function<void(const T&)> visit) const {
        preOrderHelper(root_.get(), visit);
    }
    
    void postOrder(std::function<void(const T&)> visit) const {
        postOrderHelper(root_.get(), visit);
    }
    
    // Level-order traversal (BFS)
    void levelOrder(std::function<void(const T&)> visit) const {
        if (!root_) return;
        
        std::queue<const Node*> q;
        q.push(root_.get());
        
        while (!q.empty()) {
            const Node* current = q.front();
            q.pop();
            
            visit(current->data);
            
            if (current->left) q.push(current->left.get());
            if (current->right) q.push(current->right.get());
        }
    }
    
    // Utility functions
    bool empty() const noexcept { return root_ == nullptr; }
    size_t size() const noexcept { return size_; }
    int height() const { return heightHelper(root_.get()); }
    
    void clear() {
        root_.reset();
        size_ = 0;
    }
};

} // namespace DSA
