#pragma once

#include <vector>
#include <algorithm>
#include <functional>

namespace DSA {
namespace Algorithms {

/**
 * @brief Quick Sort implementation
 * 
 * Time Complexity:
 * - Average: O(n log n)
 * - Worst: O(n²)
 * 
 * Space Complexity: O(log n) due to recursion
 */
template<typename T>
void quickSort(std::vector<T>& arr, int left, int right) {
    if (left >= right) return;
    
    // Partition
    T pivot = arr[right];
    int i = left - 1;
    
    for (int j = left; j < right; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    
    std::swap(arr[i + 1], arr[right]);
    int pivotIndex = i + 1;
    
    // Recursively sort
    quickSort(arr, left, pivotIndex - 1);
    quickSort(arr, pivotIndex + 1, right);
}

template<typename T>
void quickSort(std::vector<T>& arr) {
    if (!arr.empty()) {
        quickSort(arr, 0, arr.size() - 1);
    }
}

/**
 * @brief Merge Sort implementation
 * 
 * Time Complexity: O(n log n) guaranteed
 * Space Complexity: O(n)
 */
template<typename T>
void merge(std::vector<T>& arr, int left, int mid, int right) {
    std::vector<T> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    std::vector<T> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);
    
    int i = 0, j = 0, k = left;
    
    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = std::move(leftArr[i++]);
        } else {
            arr[k++] = std::move(rightArr[j++]);
        }
    }
    
    while (i < leftArr.size()) {
        arr[k++] = std::move(leftArr[i++]);
    }
    
    while (j < rightArr.size()) {
        arr[k++] = std::move(rightArr[j++]);
    }
}

template<typename T>
void mergeSort(std::vector<T>& arr, int left, int right) {
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

template<typename T>
void mergeSort(std::vector<T>& arr) {
    if (!arr.empty()) {
        mergeSort(arr, 0, arr.size() - 1);
    }
}

/**
 * @brief Heap Sort implementation
 * 
 * Time Complexity: O(n log n) guaranteed
 * Space Complexity: O(1)
 */
template<typename T>
void heapify(std::vector<T>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

template<typename T>
void heapSort(std::vector<T>& arr) {
    int n = arr.size();
    
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i);
    }
    
    // Extract elements from heap
    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

/**
 * @brief Binary Search implementation
 * 
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 * 
 * Note: Array must be sorted
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

/**
 * @brief Recursive Binary Search
 * 
 * Time Complexity: O(log n)
 * Space Complexity: O(log n) due to recursion
 */
template<typename T>
int binarySearchRecursive(const std::vector<T>& arr, const T& target, int left, int right) {
    if (left > right) return -1;
    
    int mid = left + (right - left) / 2;
    
    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] < target) {
        return binarySearchRecursive(arr, target, mid + 1, right);
    } else {
        return binarySearchRecursive(arr, target, left, mid - 1);
    }
}

template<typename T>
int binarySearchRecursive(const std::vector<T>& arr, const T& target) {
    return binarySearchRecursive(arr, target, 0, arr.size() - 1);
}

/**
 * @brief Linear Search
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
    return -1;
}

/**
 * @brief Check if array is sorted
 * 
 * Time Complexity: O(n)
 */
template<typename T>
bool isSorted(const std::vector<T>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Find kth smallest element using Quick Select
 * 
 * Time Complexity:
 * - Average: O(n)
 * - Worst: O(n²)
 */
template<typename T>
T quickSelect(std::vector<T>& arr, int left, int right, int k) {
    if (left == right) return arr[left];
    
    // Partition
    T pivot = arr[right];
    int i = left - 1;
    
    for (int j = left; j < right; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    
    std::swap(arr[i + 1], arr[right]);
    int pivotIndex = i + 1;
    
    if (k == pivotIndex) {
        return arr[k];
    } else if (k < pivotIndex) {
        return quickSelect(arr, left, pivotIndex - 1, k);
    } else {
        return quickSelect(arr, pivotIndex + 1, right, k);
    }
}

template<typename T>
T quickSelect(std::vector<T> arr, int k) {
    if (k < 0 || k >= arr.size()) {
        throw std::out_of_range("k is out of range");
    }
    return quickSelect(arr, 0, arr.size() - 1, k);
}

} // namespace Algorithms
} // namespace DSA
