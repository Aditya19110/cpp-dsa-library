#include <iostream>
#include <string>
#include <vector>
#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "BST.hpp"
#include "AVLTree.hpp"
#include "Graph.hpp"
#include "HashTable.hpp"
#include "Algorithms.hpp"

// Example 1: Using Stack for balanced parentheses
bool areParenthesesBalanced(const std::string& expression) {
    DSA::Stack<char> stack;
    
    for (char ch : expression) {
        if (ch == '(' || ch == '{' || ch == '[') {
            stack.push(ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (stack.empty()) return false;
            
            char top = stack.top();
            stack.pop();
            
            if ((ch == ')' && top != '(') ||
                (ch == '}' && top != '{') ||
                (ch == ']' && top != '[')) {
                return false;
            }
        }
    }
    
    return stack.empty();
}

// Example 2: Using Queue for BFS level-order processing
void printLevels() {
    std::cout << "\n=== Level-order Processing with Queue ===\n";
    DSA::Queue<std::string> tasks;
    
    tasks.enqueue("Task 1: Initialize");
    tasks.enqueue("Task 2: Process");
    tasks.enqueue("Task 3: Finalize");
    
    int level = 1;
    while (!tasks.empty()) {
        std::cout << "Level " << level++ << ": " << tasks.front() << "\n";
        tasks.dequeue();
    }
}

// Example 3: Using Hash Table for word frequency counter
void wordFrequencyCounter() {
    std::cout << "\n=== Word Frequency Counter ===\n";
    DSA::HashTable<std::string, int> frequency;
    
    std::vector<std::string> words = {
        "hello", "world", "hello", "cpp", "world", "hello", "programming"
    };
    
    for (const auto& word : words) {
        if (frequency.contains(word)) {
            frequency[word] = frequency.get(word).value() + 1;
        } else {
            frequency.insert(word, 1);
        }
    }
    
    std::cout << "Word frequencies:\n";
    frequency.forEach([](const std::string& word, const int& count) {
        std::cout << "  " << word << ": " << count << "\n";
    });
}

// Example 4: Using Graph for social network
void socialNetworkExample() {
    std::cout << "\n=== Social Network (Graph) ===\n";
    DSA::Graph<std::string> network(false); // Undirected
    
    network.addEdge("Alice", "Bob");
    network.addEdge("Alice", "Charlie");
    network.addEdge("Bob", "David");
    network.addEdge("Charlie", "David");
    network.addEdge("David", "Eve");
    
    std::cout << "Friends of Alice (BFS): ";
    network.BFS("Alice", [](const std::string& name) {
        std::cout << name << " ";
    });
    std::cout << "\n";
    
    // Find shortest path using Dijkstra
    auto distances = network.dijkstra("Alice");
    std::cout << "Distance from Alice to Eve: " << distances["Eve"] << " connections\n";
}

// Example 5: Using AVL Tree for maintaining sorted data
void sortedDataMaintenance() {
    std::cout << "\n=== Maintaining Sorted Data with AVL Tree ===\n";
    DSA::AVLTree<int> scores;
    
    // Insert scores (automatically maintains sorted order)
    std::vector<int> newScores = {85, 92, 78, 95, 88, 76, 99};
    for (int score : newScores) {
        scores.insert(score);
    }
    
    std::cout << "Scores in sorted order: ";
    scores.inOrder([](const int& score) {
        std::cout << score << " ";
    });
    std::cout << "\n";
    
    std::cout << "Tree height (balanced): " << scores.height() << "\n";
}

// Example 6: Comprehensive sorting benchmark
void sortingBenchmark() {
    std::cout << "\n=== Sorting Algorithm Comparison ===\n";
    
    std::vector<int> data = {15, 3, 9, 8, 5, 2, 7, 1, 6, 4};
    
    auto data1 = data;
    auto data2 = data;
    auto data3 = data;
    
    std::cout << "Original: ";
    for (int val : data) std::cout << val << " ";
    std::cout << "\n";
    
    DSA::Algorithms::quickSort(data1);
    std::cout << "Quick Sort: ";
    for (int val : data1) std::cout << val << " ";
    std::cout << "\n";
    
    DSA::Algorithms::mergeSort(data2);
    std::cout << "Merge Sort: ";
    for (int val : data2) std::cout << val << " ";
    std::cout << "\n";
    
    DSA::Algorithms::heapSort(data3);
    std::cout << "Heap Sort:  ";
    for (int val : data3) std::cout << val << " ";
    std::cout << "\n";
}

// Example 7: Using Dynamic Array with move semantics
void moveSemanticsDemonstration() {
    std::cout << "\n=== Move Semantics Demonstration ===\n";
    
    DSA::DynamicArray<std::string> arr1;
    arr1.push_back("C++");
    arr1.push_back("is");
    arr1.push_back("awesome");
    
    std::cout << "Original array size: " << arr1.size() << "\n";
    
    // Move array (efficient, no copying)
    DSA::DynamicArray<std::string> arr2 = std::move(arr1);
    std::cout << "After move - arr1 size: " << arr1.size() << ", arr2 size: " << arr2.size() << "\n";
}

int main() {
    std::cout << "╔════════════════════════════════════╗\n";
    std::cout << "║  DSA Library - Usage Examples     ║\n";
    std::cout << "╚════════════════════════════════════╝\n";
    
    try {
        // Example 1: Balanced Parentheses
        std::cout << "\n=== Balanced Parentheses Checker ===\n";
        std::string expr1 = "{[()]}";
        std::string expr2 = "{[(])}";
        std::cout << expr1 << " is " << (areParenthesesBalanced(expr1) ? "balanced" : "not balanced") << "\n";
        std::cout << expr2 << " is " << (areParenthesesBalanced(expr2) ? "balanced" : "not balanced") << "\n";
        
        printLevels();
        wordFrequencyCounter();
        socialNetworkExample();
        sortedDataMaintenance();
        sortingBenchmark();
        moveSemanticsDemonstration();
        
        std::cout << "\n✓ All examples completed successfully!\n";
    } catch (const std::exception& e) {
        std::cerr << "\n✗ Error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}
