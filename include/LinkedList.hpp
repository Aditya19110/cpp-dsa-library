#pragma once

#include <memory>
#include <stdexcept>
#include <initializer_list>

namespace DSA {

/**
 * @brief Doubly Linked List implementation with smart pointers
 * 
 * Time Complexities:
 * - Insert at front: O(1)
 * - Insert at back: O(1)
 * - Remove at front: O(1)
 * - Remove at back: O(1)
 * - Search: O(n)
 * - Access by index: O(n)
 * 
 * Space Complexity: O(n)
 */
template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        Node* prev;
        
        explicit Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
        explicit Node(T&& value) : data(std::move(value)), next(nullptr), prev(nullptr) {}
    };
    
    std::unique_ptr<Node> head_;
    Node* tail_;
    size_t size_;

public:
    LinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}
    
    LinkedList(std::initializer_list<T> init) : head_(nullptr), tail_(nullptr), size_(0) {
        for (const auto& item : init) {
            push_back(item);
        }
    }
    
    // Move constructor
    LinkedList(LinkedList&& other) noexcept
        : head_(std::move(other.head_)),
          tail_(other.tail_),
          size_(other.size_) {
        other.tail_ = nullptr;
        other.size_ = 0;
    }
    
    // Move assignment
    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            head_ = std::move(other.head_);
            tail_ = other.tail_;
            size_ = other.size_;
            other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }
    
    // Delete copy operations
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;
    
    // Insert at front - O(1)
    void push_front(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        if (!head_) {
            tail_ = newNode.get();
        } else {
            newNode->next = std::move(head_);
            newNode->next->prev = newNode.get();
        }
        head_ = std::move(newNode);
        ++size_;
    }
    
    void push_front(T&& value) {
        auto newNode = std::make_unique<Node>(std::move(value));
        if (!head_) {
            tail_ = newNode.get();
        } else {
            newNode->next = std::move(head_);
            newNode->next->prev = newNode.get();
        }
        head_ = std::move(newNode);
        ++size_;
    }
    
    // Insert at back - O(1)
    void push_back(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        if (!tail_) {
            head_ = std::move(newNode);
            tail_ = head_.get();
        } else {
            newNode->prev = tail_;
            tail_->next = std::move(newNode);
            tail_ = tail_->next.get();
        }
        ++size_;
    }
    
    void push_back(T&& value) {
        auto newNode = std::make_unique<Node>(std::move(value));
        if (!tail_) {
            head_ = std::move(newNode);
            tail_ = head_.get();
        } else {
            newNode->prev = tail_;
            tail_->next = std::move(newNode);
            tail_ = tail_->next.get();
        }
        ++size_;
    }
    
    // Remove from front - O(1)
    void pop_front() {
        if (!head_) {
            throw std::out_of_range("List is empty");
        }
        head_ = std::move(head_->next);
        if (head_) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        --size_;
    }
    
    // Remove from back - O(1)
    void pop_back() {
        if (!tail_) {
            throw std::out_of_range("List is empty");
        }
        if (tail_->prev) {
            tail_ = tail_->prev;
            tail_->next.reset();
        } else {
            head_.reset();
            tail_ = nullptr;
        }
        --size_;
    }
    
    // Access front element
    T& front() {
        if (!head_) throw std::out_of_range("List is empty");
        return head_->data;
    }
    
    const T& front() const {
        if (!head_) throw std::out_of_range("List is empty");
        return head_->data;
    }
    
    // Access back element
    T& back() {
        if (!tail_) throw std::out_of_range("List is empty");
        return tail_->data;
    }
    
    const T& back() const {
        if (!tail_) throw std::out_of_range("List is empty");
        return tail_->data;
    }
    
    // Utility functions
    size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }
    
    void clear() {
        head_.reset();
        tail_ = nullptr;
        size_ = 0;
    }
    
    // Search for value - O(n)
    bool contains(const T& value) const {
        Node* current = head_.get();
        while (current) {
            if (current->data == value) return true;
            current = current->next.get();
        }
        return false;
    }
};

} // namespace DSA
