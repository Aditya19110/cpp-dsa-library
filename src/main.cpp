#include <iostream>
#include <string>
#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "BST.hpp"
#include "AVLTree.hpp"
#include "Graph.hpp"
#include "HashTable.hpp"
#include "Algorithms.hpp"

void demonstrateDynamicArray() {
    std::cout << "\n=== Dynamic Array Demo ===\n";
    DSA::DynamicArray<int> arr;
    
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);
    
    std::cout << "Array elements: ";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\nSize: " << arr.size() << ", Capacity: " << arr.capacity() << "\n";
}

void demonstrateLinkedList() {
    std::cout << "\n=== Linked List Demo ===\n";
    DSA::LinkedList<int> list = {1, 2, 3, 4, 5};
    
    list.push_front(0);
    list.push_back(6);
    
    std::cout << "Front: " << list.front() << ", Back: " << list.back() << "\n";
    std::cout << "Size: " << list.size() << "\n";
    std::cout << "Contains 3: " << (list.contains(3) ? "Yes" : "No") << "\n";
}

void demonstrateStack() {
    std::cout << "\n=== Stack Demo ===\n";
    DSA::Stack<std::string> stack;
    
    stack.push("First");
    stack.push("Second");
    stack.push("Third");
    
    std::cout << "Top element: " << stack.top() << "\n";
    stack.pop();
    std::cout << "After pop, top: " << stack.top() << "\n";
    std::cout << "Size: " << stack.size() << "\n";
}

void demonstrateQueue() {
    std::cout << "\n=== Queue Demo ===\n";
    DSA::Queue<int> queue;
    
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    
    std::cout << "Front: " << queue.front() << ", Back: " << queue.back() << "\n";
    queue.dequeue();
    std::cout << "After dequeue, front: " << queue.front() << "\n";
}

void demonstrateBST() {
    std::cout << "\n=== Binary Search Tree Demo ===\n";
    DSA::BST<int> bst;
    
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    
    std::cout << "In-order traversal: ";
    bst.inOrder([](const int& val) { std::cout << val << " "; });
    std::cout << "\n";
    
    std::cout << "Search 40: " << (bst.search(40) ? "Found" : "Not found") << "\n";
    std::cout << "Height: " << bst.height() << "\n";
}

void demonstrateAVLTree() {
    std::cout << "\n=== AVL Tree Demo ===\n";
    DSA::AVLTree<int> avl;
    
    // Insert elements that would create imbalance in regular BST
    for (int i = 1; i <= 7; ++i) {
        avl.insert(i);
    }
    
    std::cout << "In-order traversal: ";
    avl.inOrder([](const int& val) { std::cout << val << " "; });
    std::cout << "\n";
    
    std::cout << "Height (balanced): " << avl.height() << "\n";
    std::cout << "Search 5: " << (avl.search(5) ? "Found" : "Not found") << "\n";
}

void demonstrateGraph() {
    std::cout << "\n=== Graph Demo ===\n";
    DSA::Graph<int> graph(false); // Undirected graph
    
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    
    std::cout << "BFS from vertex 0: ";
    graph.BFS(0, [](const int& val) { std::cout << val << " "; });
    std::cout << "\n";
    
    std::cout << "DFS from vertex 0: ";
    graph.DFS(0, [](const int& val) { std::cout << val << " "; });
    std::cout << "\n";
    
    std::cout << "Vertices: " << graph.vertexCount() << ", Edges: " << graph.edgeCount() << "\n";
}

void demonstrateHashTable() {
    std::cout << "\n=== Hash Table Demo ===\n";
    DSA::HashTable<std::string, int> table;
    
    table.insert("apple", 5);
    table.insert("banana", 3);
    table.insert("orange", 7);
    
    std::cout << "apple: " << table["apple"] << "\n";
    std::cout << "banana: " << table["banana"] << "\n";
    
    std::cout << "Contains 'orange': " << (table.contains("orange") ? "Yes" : "No") << "\n";
    std::cout << "Size: " << table.size() << "\n";
    std::cout << "Load factor: " << table.loadFactor() << "\n";
}

void demonstrateAlgorithms() {
    std::cout << "\n=== Algorithms Demo ===\n";
    
    // Sorting
    std::vector<int> arr1 = {64, 34, 25, 12, 22, 11, 90};
    std::vector<int> arr2 = arr1;
    std::vector<int> arr3 = arr1;
    
    DSA::Algorithms::quickSort(arr1);
    std::cout << "Quick Sort: ";
    for (int val : arr1) std::cout << val << " ";
    std::cout << "\n";
    
    DSA::Algorithms::mergeSort(arr2);
    std::cout << "Merge Sort: ";
    for (int val : arr2) std::cout << val << " ";
    std::cout << "\n";
    
    DSA::Algorithms::heapSort(arr3);
    std::cout << "Heap Sort:  ";
    for (int val : arr3) std::cout << val << " ";
    std::cout << "\n";
    
    // Binary Search
    int index = DSA::Algorithms::binarySearch(arr1, 25);
    std::cout << "Binary Search for 25: " << (index != -1 ? "Found at index " + std::to_string(index) : "Not found") << "\n";
    
    // Quick Select (find 3rd smallest)
    std::vector<int> arr4 = {7, 10, 4, 3, 20, 15};
    int kth = DSA::Algorithms::quickSelect(arr4, 2); // 0-indexed, so 2 = 3rd smallest
    std::cout << "3rd smallest element: " << kth << "\n";
}

int main() {
    std::cout << "╔════════════════════════════════════════╗\n";
    std::cout << "║  Custom C++ DSA Library Demonstration ║\n";
    std::cout << "╚════════════════════════════════════════╝\n";
    
    try {
        demonstrateDynamicArray();
        demonstrateLinkedList();
        demonstrateStack();
        demonstrateQueue();
        demonstrateBST();
        demonstrateAVLTree();
        demonstrateGraph();
        demonstrateHashTable();
        demonstrateAlgorithms();
        
        std::cout << "\n✓ All demonstrations completed successfully!\n";
    } catch (const std::exception& e) {
        std::cerr << "\n✗ Error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}
