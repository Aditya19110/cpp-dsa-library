#pragma once

#include <stdexcept>    // For exceptions

namespace DSA {

/**
 * @brief Dynamic Array - A resizable array
 * 
 * A simple array that grows automatically when full.
 * Similar to std::vector but simpler.
 */
template<typename T>
class DynamicArray {
private:
    T* data_;            // Pointer to the array
    size_t size_;        // Number of elements
    size_t capacity_;    // Total space allocated

    // Helper function to double the capacity when array is full
    void resize() {
        size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        T* newData = new T[newCapacity];
        
        // Copy old data to new array
        for (size_t i = 0; i < size_; ++i) {
            newData[i] = data_[i];
        }
        
        delete[] data_;  // Free old memory
        data_ = newData;
        capacity_ = newCapacity;
    }

public:
    // Constructor - creates empty array
    DynamicArray() : data_(nullptr), size_(0), capacity_(0) {}
    
    // Constructor with initial capacity
    explicit DynamicArray(size_t capacity) 
        : data_(new T[capacity]), size_(0), capacity_(capacity) {}
    
    // Destructor - cleans up memory
    ~DynamicArray() {
        delete[] data_;
    }
    
    // Copy constructor
    DynamicArray(const DynamicArray& other) 
        : data_(new T[other.capacity_]), size_(other.size_), capacity_(other.capacity_) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    
    // Copy assignment
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] data_;
            data_ = new T[other.capacity_];
            size_ = other.size_;
            capacity_ = other.capacity_;
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    }
    
    // Add element at the end
    void push_back(const T& value) {
        if (size_ >= capacity_) {
            resize();
        }
        data_[size_++] = value;
    }
    
    // Remove element from the end
    void pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("Array is empty");
        }
        --size_;
    }
    
    // Access element by index
    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of bounds");
        }
        return data_[index];
    }
    
    // Access element by index (const version)
    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of bounds");
        }
        return data_[index];
    }
    
    // Get number of elements
    size_t size() const { return size_; }
    
    // Get capacity
    size_t capacity() const { return capacity_; }
    
    // Check if empty
    bool empty() const { return size_ == 0; }
    
    // Clear all elements
    void clear() {
        size_ = 0;
    }
    
    // Iterator support for range-based for loops
    T* begin() { return data_; }
    T* end() { return data_ + size_; }
    const T* begin() const { return data_; }
    const T* end() const { return data_ + size_; }
};

} // namespace DSA
