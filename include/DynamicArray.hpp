#pragma once

#include <memory>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>

namespace DSA {

/**
 * @brief Template-based dynamic array with automatic resizing
 * 
 * Time Complexities:
 * - Access: O(1)
 * - Push back: O(1) amortized
 * - Pop back: O(1)
 * - Insert/Remove: O(n)
 * 
 * Space Complexity: O(n)
 */
template<typename T>
class DynamicArray {
private:
    std::unique_ptr<T[]> data_;
    size_t size_;
    size_t capacity_;

    void resize() {
        size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        auto newData = std::make_unique<T[]>(newCapacity);
        
        // Move elements to new array
        for (size_t i = 0; i < size_; ++i) {
            newData[i] = std::move(data_[i]);
        }
        
        data_ = std::move(newData);
        capacity_ = newCapacity;
    }

public:
    // Constructor
    DynamicArray() : data_(nullptr), size_(0), capacity_(0) {}
    
    // Constructor with initial capacity
    explicit DynamicArray(size_t capacity) 
        : data_(std::make_unique<T[]>(capacity)), size_(0), capacity_(capacity) {}
    
    // Initializer list constructor
    DynamicArray(std::initializer_list<T> init) 
        : data_(std::make_unique<T[]>(init.size())), 
          size_(init.size()), 
          capacity_(init.size()) {
        std::copy(init.begin(), init.end(), data_.get());
    }
    
    // Move constructor
    DynamicArray(DynamicArray&& other) noexcept
        : data_(std::move(other.data_)),
          size_(other.size_),
          capacity_(other.capacity_) {
        other.size_ = 0;
        other.capacity_ = 0;
    }
    
    // Move assignment
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }
    
    // Delete copy operations
    DynamicArray(const DynamicArray&) = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;
    
    // Add element at the end - O(1) amortized
    void push_back(const T& value) {
        if (size_ >= capacity_) {
            resize();
        }
        data_[size_++] = value;
    }
    
    void push_back(T&& value) {
        if (size_ >= capacity_) {
            resize();
        }
        data_[size_++] = std::move(value);
    }
    
    // Remove element from the end - O(1)
    void pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("Array is empty");
        }
        --size_;
    }
    
    // Access element - O(1)
    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of bounds");
        }
        return data_[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of bounds");
        }
        return data_[index];
    }
    
    // Size and capacity
    size_t size() const noexcept { return size_; }
    size_t capacity() const noexcept { return capacity_; }
    bool empty() const noexcept { return size_ == 0; }
    
    // Clear array
    void clear() noexcept {
        size_ = 0;
    }
    
    // Reserve capacity
    void reserve(size_t newCapacity) {
        if (newCapacity > capacity_) {
            auto newData = std::make_unique<T[]>(newCapacity);
            for (size_t i = 0; i < size_; ++i) {
                newData[i] = std::move(data_[i]);
            }
            data_ = std::move(newData);
            capacity_ = newCapacity;
        }
    }
    
    // Iterator support
    T* begin() { return data_.get(); }
    T* end() { return data_.get() + size_; }
    const T* begin() const { return data_.get(); }
    const T* end() const { return data_.get() + size_; }
};

} // namespace DSA
