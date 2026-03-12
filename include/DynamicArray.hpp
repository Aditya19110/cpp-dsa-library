#pragma once

#include <memory>       // For smart pointers (unique_ptr)
#include <stdexcept>    // For exceptions (out_of_range)
#include <algorithm>    // For std::copy
#include <initializer_list>  // For {1, 2, 3} initialization

namespace DSA {

/**
 * @brief Dynamic Array - A resizable array similar to std::vector
 * 
 * LEARNING NOTES:
 * - Regular arrays in C++ have fixed size: int arr[10];
 * - This class creates an array that can grow automatically
 * - When full, we create a bigger array and copy data over
 * 
 * WHY TEMPLATES?
 * - template<typename T> means this works with ANY type
 * - DynamicArray<int>, DynamicArray<string>, DynamicArray<MyClass> all work!
 * 
 * Time Complexities:
 * - Access arr[i]: O(1) - Direct memory access, instant
 * - Push back: O(1) amortized - Usually fast, occasionally slow when resizing
 * - Pop back: O(1) - Just decrease size counter
 * - Insert/Remove middle: O(n) - Need to shift all elements after
 * 
 * Space Complexity: O(n) - Stores n elements
 */
template<typename T>
class DynamicArray {
private:
    // MEMBER VARIABLES
    // Why unique_ptr instead of raw pointer (T*)?
    // - Automatic cleanup: No need to manually delete[]
    // - Prevents memory leaks: Deletes automatically when object destroyed
    // - Move-only: Can't accidentally copy and double-delete
    std::unique_ptr<T[]> data_;      // Points to actual array in memory
    size_t size_;                     // How many elements currently stored
    size_t capacity_;                 // Total space allocated

    /**
     * @brief Private helper - Doubles capacity when array is full
     * 
     * LEARNING NOTE ON GROWTH STRATEGY:
     * - Could grow by fixed amount (capacity += 10) - BAD: O(n²) total time
     * - We double capacity (capacity *= 2) - GOOD: O(1) amortized time
     * 
     * Why doubling is better:
     * - Adding n elements with +10 strategy: ~n² copies total
     * - Adding n elements with ×2 strategy: ~2n copies total
     */
    void resize() {
        size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        auto newData = std::make_unique<T[]>(newCapacity);
        for (size_t i = 0; i < size_; ++i) {
            newData[i] = std::move(data_[i]);
        }
        data_ = std::move(newData);
        capacity_ = newCapacity;
    }

public:
    // CONSTRUCTORS
    
    /**
     * @brief Default constructor - Creates empty array
     * 
     * LEARNING NOTE:
     * The : data_(nullptr), size_(0)... is called "member initializer list"
     * It's more efficient than assigning in the constructor body
     */
    DynamicArray() : data_(nullptr), size_(0), capacity_(0) {}
    
    /**
     * @brief Constructor with reserved capacity
     * 
     * Use when you know roughly how many elements you'll add
     * Avoids repeated resizing
     * 
     * Example: DynamicArray<int> arr(100); // Reserve space for 100 ints
     */
    explicit DynamicArray(size_t capacity) 
        : data_(std::make_unique<T[]>(capacity)), size_(0), capacity_(capacity) {}
    
    /**
     * @brief Initializer list constructor
     * 
     * Allows syntax: DynamicArray<int> arr = {1, 2, 3, 4, 5};
     * Very convenient for testing!
     */
    DynamicArray(std::initializer_list<T> init) 
        : data_(std::make_unique<T[]>(init.size())), 
          size_(init.size()), 
          capacity_(init.size()) {
        std::copy(init.begin(), init.end(), data_.get());
    }
    
    /**
     * @brief Move constructor - Transfer ownership
     * 
     * LEARNING NOTE ON MOVE SEMANTICS:
     * Instead of copying all elements (slow), we "steal" the pointer (fast)
     * The && means "rvalue reference" - temporary object that's about to die
     * After this, 'other' is left in valid but empty state
     */
    DynamicArray(DynamicArray&& other) noexcept 
        : data_(std::move(other.data_)), 
          size_(other.size_), 
          capacity_(other.capacity_) {
        other.size_ = 0;
        other.capacity_ = 0;
    }
    
    /**
     * @brief Move assignment operator
     * 
     * Handles: arr1 = std::move(arr2);
     */
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
    
    // Delete copy operations to prevent accidental copies
    DynamicArray(const DynamicArray&) = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;
    
    // MAIN OPERATIONS
    
    /**
     * @brief Add element at the end
     * 
     * Time Complexity: O(1) amortized
     * - Most calls: O(1) - Just add to end
     * - Occasionally: O(n) - When resize needed
     * - Average over many calls: O(1) "amortized"
     * 
     * Example:
     *   arr.push_back(42);
     *   arr.push_back(100);
     */
    void push_back(const T& value) {
        if (size_ >= capacity_) {
            resize();  // Make room if full
        }
        data_[size_++] = value;  // Add at end, then increment size
    }
    
    /**
     * @brief Add element using move semantics
     * 
     * For large objects (strings, vectors), moving is faster than copying
     * Example: arr.push_back(std::move(largeString));
     */
    void push_back(T&& value) {
        if (size_ >= capacity_) {
            resize();
        }
        data_[size_++] = std::move(value);  // Move instead of copy
    }
    
    /**
     * @brief Remove element from the end
     * 
     * Time Complexity: O(1)
     * Just decrements size, doesn't actually delete element
     * (Will be overwritten when new element added)
     */
    void pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("Array is empty");
        }
        --size_;  // Just decrease size counter
    }
    
    /**
     * @brief Access element by index - READ/WRITE
     * 
     * Time Complexity: O(1) - Direct memory access
     * 
     * Example:
     *   arr[0] = 10;        // Write
     *   int x = arr[0];     // Read
     * 
     * LEARNING NOTE:
     * operator[] is "overloading" - making [] work with our class
     * Two versions: non-const (can modify) and const (read-only)
     */
    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of bounds");
        }
        return data_[index];  // Return reference so caller can modify
    }
    
    /**
     * @brief Access element by index - READ ONLY
     * 
     * This const version is called when array itself is const
     */
    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of bounds");
        }
        return data_[index];
    }
    
    // UTILITY FUNCTIONS
    
    /**
     * @brief Get number of elements
     * 
     * LEARNING NOTE:
     * - const means this function doesn't modify the object
     * - noexcept means this never throws exceptions
     * - Both help compiler optimize and catch errors
     */
    size_t size() const noexcept { return size_; }
    
    /**
     * @brief Get total allocated space
     * 
     * capacity >= size always true
     * Extra capacity = room to grow without resizing
     */
    size_t capacity() const noexcept { return capacity_; }
    
    /**
     * @brief Check if array is empty
     * 
     * More readable than: if (arr.size() == 0)
     */
    bool empty() const noexcept { return size_ == 0; }
    
    /**
     * @brief Clear all elements
     * 
     * Keeps allocated memory (capacity unchanged)
     * Only resets size to 0
     */
    void clear() noexcept {
        size_ = 0;  // Elements still in memory, but considered "removed"
    }
    
    /**
     * @brief Reserve space for future elements
     * 
     * Use when you know you'll add many elements
     * Prevents multiple resizes
     * 
     * Example:
     *   arr.reserve(1000);  // Allocate space for 1000 elements
     *   for (int i = 0; i < 1000; i++) {
     *       arr.push_back(i);  // No resize needed!
     *   }
     */
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
    
    // ITERATOR SUPPORT
    // This allows: for (auto& elem : arr) { ... }
    
    /**
     * @brief Get pointer to first element
     * 
     * LEARNING NOTE:
     * Iterators let you use range-based for loops
     * begin() and end() define the range
     */
    T* begin() { return data_.get(); }  // data_.get() gets raw pointer
    T* end() { return data_.get() + size_; }  // Pointer arithmetic
    const T* begin() const { return data_.get(); }
    const T* end() const { return data_.get() + size_; }
};

} // namespace DSA
