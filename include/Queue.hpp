#pragma once

#include <memory>
#include <stdexcept>
#include <initializer_list>

namespace DSA {

/**
 * @brief Queue (FIFO) implementation using linked list
 * 
 * Time Complexities:
 * - Enqueue: O(1)
 * - Dequeue: O(1)
 * - Front: O(1)
 * 
 * Space Complexity: O(n)
 */
template<typename T>
class Queue {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        
        explicit Node(const T& value) : data(value), next(nullptr) {}
        explicit Node(T&& value) : data(std::move(value)), next(nullptr) {}
    };
    
    std::unique_ptr<Node> front_;
    Node* back_;
    size_t size_;

public:
    Queue() : front_(nullptr), back_(nullptr), size_(0) {}
    
    Queue(std::initializer_list<T> init) : front_(nullptr), back_(nullptr), size_(0) {
        for (const auto& item : init) {
            enqueue(item);
        }
    }
    
    // Move constructor
    Queue(Queue&& other) noexcept
        : front_(std::move(other.front_)),
          back_(other.back_),
          size_(other.size_) {
        other.back_ = nullptr;
        other.size_ = 0;
    }
    
    // Move assignment
    Queue& operator=(Queue&& other) noexcept {
        if (this != &other) {
            front_ = std::move(other.front_);
            back_ = other.back_;
            size_ = other.size_;
            other.back_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }
    
    // Delete copy operations
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
    
    // Add element to back - O(1)
    void enqueue(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        if (!back_) {
            front_ = std::move(newNode);
            back_ = front_.get();
        } else {
            back_->next = std::move(newNode);
            back_ = back_->next.get();
        }
        ++size_;
    }
    
    void enqueue(T&& value) {
        auto newNode = std::make_unique<Node>(std::move(value));
        if (!back_) {
            front_ = std::move(newNode);
            back_ = front_.get();
        } else {
            back_->next = std::move(newNode);
            back_ = back_->next.get();
        }
        ++size_;
    }
    
    // Remove element from front - O(1)
    void dequeue() {
        if (!front_) {
            throw std::out_of_range("Queue is empty");
        }
        front_ = std::move(front_->next);
        if (!front_) {
            back_ = nullptr;
        }
        --size_;
    }
    
    // Access front element - O(1)
    T& front() {
        if (!front_) {
            throw std::out_of_range("Queue is empty");
        }
        return front_->data;
    }
    
    const T& front() const {
        if (!front_) {
            throw std::out_of_range("Queue is empty");
        }
        return front_->data;
    }
    
    // Access back element - O(1)
    T& back() {
        if (!back_) {
            throw std::out_of_range("Queue is empty");
        }
        return back_->data;
    }
    
    const T& back() const {
        if (!back_) {
            throw std::out_of_range("Queue is empty");
        }
        return back_->data;
    }
    
    // Utility functions
    bool empty() const noexcept { return front_ == nullptr; }
    size_t size() const noexcept { return size_; }
    
    void clear() {
        front_.reset();
        back_ = nullptr;
        size_ = 0;
    }
};

} // namespace DSA
