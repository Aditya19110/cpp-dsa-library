#pragma once

#include <memory>
#include <stdexcept>
#include <initializer_list>

namespace DSA {

/**
 * @brief Stack (LIFO) implementation using linked list
 * 
 * Time Complexities:
 * - Push: O(1)
 * - Pop: O(1)
 * - Top: O(1)
 * 
 * Space Complexity: O(n)
 */
template<typename T>
class Stack {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        
        explicit Node(const T& value) : data(value), next(nullptr) {}
        explicit Node(T&& value) : data(std::move(value)), next(nullptr) {}
    };
    
    std::unique_ptr<Node> top_;
    size_t size_;

public:
    Stack() : top_(nullptr), size_(0) {}
    
    Stack(std::initializer_list<T> init) : top_(nullptr), size_(0) {
        for (const auto& item : init) {
            push(item);
        }
    }
    
    // Move constructor
    Stack(Stack&& other) noexcept
        : top_(std::move(other.top_)), size_(other.size_) {
        other.size_ = 0;
    }
    
    // Move assignment
    Stack& operator=(Stack&& other) noexcept {
        if (this != &other) {
            top_ = std::move(other.top_);
            size_ = other.size_;
            other.size_ = 0;
        }
        return *this;
    }
    
    // Delete copy operations
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;
    
    // Push element - O(1)
    void push(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        newNode->next = std::move(top_);
        top_ = std::move(newNode);
        ++size_;
    }
    
    void push(T&& value) {
        auto newNode = std::make_unique<Node>(std::move(value));
        newNode->next = std::move(top_);
        top_ = std::move(newNode);
        ++size_;
    }
    
    // Pop element - O(1)
    void pop() {
        if (!top_) {
            throw std::out_of_range("Stack is empty");
        }
        top_ = std::move(top_->next);
        --size_;
    }
    
    // Access top element - O(1)
    T& top() {
        if (!top_) {
            throw std::out_of_range("Stack is empty");
        }
        return top_->data;
    }
    
    const T& top() const {
        if (!top_) {
            throw std::out_of_range("Stack is empty");
        }
        return top_->data;
    }
    
    // Utility functions
    bool empty() const noexcept { return top_ == nullptr; }
    size_t size() const noexcept { return size_; }
    
    void clear() {
        top_.reset();
        size_ = 0;
    }
};

} // namespace DSA
