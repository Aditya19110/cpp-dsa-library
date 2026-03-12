#pragma once

#include <vector>
#include <algorithm>

namespace DSA {
namespace Algorithms {

/**
 * @brief Bubble Sort - Simple sorting algorithm
 * 
 * Time Complexity: O(n²)
 * Space Complexity: O(1)
 */
template<typename T>
void bubbleSort(std::vector<T>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

/**
 * @brief Selection Sort - Find minimum and place it at beginning
 * 
 * Time Complexity: O(n²)
 * Space Complexity: O(1)
 */
template<typename T>
void selectionSort(std::vector<T>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            std::swap(arr[i], arr[minIdx]);
        }
    }
}

/**
 * @brief Linear Search - Search by checking each element
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
template<typename T>
int linearSearch(const std::vector<T>& arr, const T& target) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;  // Not found
}

/**
 * @brief Binary Search - Fast search in sorted array
 * 
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 * 
 * Note: Array must be sorted!
 */
template<typename T>
int binarySearch(const std::vector<T>& arr, const T& target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1; // Not found
}

} // namespace Algorithms
} // namespace DSA
