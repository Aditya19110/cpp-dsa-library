#pragma once

#include <vector>
#include <list>
#include <optional>
#include <functional>
#include <stdexcept>

namespace DSA {

/**
 * @brief Hash Table implementation with separate chaining
 * 
 * Time Complexities (average case):
 * - Insert: O(1)
 * - Search: O(1)
 * - Delete: O(1)
 * 
 * Time Complexities (worst case):
 * - Insert: O(n)
 * - Search: O(n)
 * - Delete: O(n)
 * 
 * Space Complexity: O(n)
 */
template<typename K, typename V>
class HashTable {
private:
    struct KeyValuePair {
        K key;
        V value;
        
        KeyValuePair(const K& k, const V& v) : key(k), value(v) {}
        KeyValuePair(K&& k, V&& v) : key(std::move(k)), value(std::move(v)) {}
    };
    
    std::vector<std::list<KeyValuePair>> buckets_;
    size_t size_;
    size_t bucketCount_;
    double maxLoadFactor_;
    std::hash<K> hasher_;
    
    // Get bucket index for key
    size_t getBucketIndex(const K& key) const {
        return hasher_(key) % bucketCount_;
    }
    
    // Rehash when load factor exceeds threshold
    void rehash() {
        size_t newBucketCount = bucketCount_ * 2;
        std::vector<std::list<KeyValuePair>> newBuckets(newBucketCount);
        
        // Rehash all existing elements
        for (auto& bucket : buckets_) {
            for (auto& pair : bucket) {
                size_t newIndex = hasher_(pair.key) % newBucketCount;
                newBuckets[newIndex].emplace_back(std::move(pair));
            }
        }
        
        buckets_ = std::move(newBuckets);
        bucketCount_ = newBucketCount;
    }
    
    // Check if rehashing is needed
    void checkLoadFactor() {
        if (loadFactor() > maxLoadFactor_) {
            rehash();
        }
    }

public:
    explicit HashTable(size_t bucketCount = 16, double maxLoadFactor = 0.75)
        : buckets_(bucketCount),
          size_(0),
          bucketCount_(bucketCount),
          maxLoadFactor_(maxLoadFactor) {}
    
    // Insert or update key-value pair - O(1) average
    void insert(const K& key, const V& value) {
        size_t index = getBucketIndex(key);
        auto& bucket = buckets_[index];
        
        // Check if key already exists
        for (auto& pair : bucket) {
            if (pair.key == key) {
                pair.value = value; // Update existing
                return;
            }
        }
        
        // Insert new key-value pair
        bucket.emplace_back(key, value);
        ++size_;
        checkLoadFactor();
    }
    
    void insert(K&& key, V&& value) {
        size_t index = getBucketIndex(key);
        auto& bucket = buckets_[index];
        
        // Check if key already exists
        for (auto& pair : bucket) {
            if (pair.key == key) {
                pair.value = std::move(value); // Update existing
                return;
            }
        }
        
        // Insert new key-value pair
        bucket.emplace_back(std::move(key), std::move(value));
        ++size_;
        checkLoadFactor();
    }
    
    // Access or insert - O(1) average
    V& operator[](const K& key) {
        size_t index = getBucketIndex(key);
        auto& bucket = buckets_[index];
        
        // Search for existing key
        for (auto& pair : bucket) {
            if (pair.key == key) {
                return pair.value;
            }
        }
        
        // Key doesn't exist, create with default value
        bucket.emplace_back(key, V{});
        ++size_;
        checkLoadFactor();
        return bucket.back().value;
    }
    
    // Get value by key - O(1) average
    std::optional<V> get(const K& key) const {
        size_t index = getBucketIndex(key);
        const auto& bucket = buckets_[index];
        
        for (const auto& pair : bucket) {
            if (pair.key == key) {
                return pair.value;
            }
        }
        
        return std::nullopt;
    }
    
    // Check if key exists - O(1) average
    bool contains(const K& key) const {
        size_t index = getBucketIndex(key);
        const auto& bucket = buckets_[index];
        
        for (const auto& pair : bucket) {
            if (pair.key == key) {
                return true;
            }
        }
        
        return false;
    }
    
    // Remove key-value pair - O(1) average
    bool remove(const K& key) {
        size_t index = getBucketIndex(key);
        auto& bucket = buckets_[index];
        
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->key == key) {
                bucket.erase(it);
                --size_;
                return true;
            }
        }
        
        return false;
    }
    
    // Utility functions
    size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }
    size_t bucketCount() const noexcept { return bucketCount_; }
    double loadFactor() const noexcept { 
        return static_cast<double>(size_) / bucketCount_; 
    }
    
    void clear() {
        for (auto& bucket : buckets_) {
            bucket.clear();
        }
        size_ = 0;
    }
    
    // Iterate over all key-value pairs
    void forEach(std::function<void(const K&, V&)> visit) {
        for (auto& bucket : buckets_) {
            for (auto& pair : bucket) {
                visit(pair.key, pair.value);
            }
        }
    }
    
    void forEach(std::function<void(const K&, const V&)> visit) const {
        for (const auto& bucket : buckets_) {
            for (const auto& pair : bucket) {
                visit(pair.key, pair.value);
            }
        }
    }
};

} // namespace DSA
