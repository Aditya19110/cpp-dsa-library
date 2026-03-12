#include <iostream>
#include <cassert>
#include <string>
#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "BST.hpp"
#include "Graph.hpp"
#include "HashTable.hpp"
#include "Algorithms.hpp"

#define TEST(name) void test_##name()
#define RUN_TEST(name) do { \
    std::cout << "Running " #name "... "; \
    test_##name(); \
    std::cout << "✓ PASSED\n"; \
} while(0)

// Dynamic Array Tests
TEST(dynamic_array_basic) {
    DSA::DynamicArray<int> arr;
    assert(arr.empty());
    
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);
    
    assert(arr.size() == 3);
    assert(arr[0] == 10);
    assert(arr[1] == 20);
    assert(arr[2] == 30);
    
    arr.pop_back();
    assert(arr.size() == 2);
}

TEST(dynamic_array_resize) {
    DSA::DynamicArray<int> arr;
    
    for (int i = 0; i < 100; ++i) {
        arr.push_back(i);
    }
    
    assert(arr.size() == 100);
    assert(arr[99] == 99);
}

// Linked List Tests
TEST(linked_list_basic) {
    DSA::LinkedList<int> list;
    
    list.push_back(1);
    list.push_back(2);
    list.push_front(0);
    
    assert(list.size() == 3);
    assert(list.front() == 0);
    assert(list.back() == 2);
    
    list.pop_front();
    assert(list.front() == 1);
}

TEST(linked_list_contains) {
    DSA::LinkedList<std::string> list = {"apple", "banana", "cherry"};
    
    assert(list.contains("banana"));
    assert(!list.contains("grape"));
}

// Stack Tests
TEST(stack_basic) {
    DSA::Stack<int> stack;
    
    stack.push(1);
    stack.push(2);
    stack.push(3);
    
    assert(stack.top() == 3);
    stack.pop();
    assert(stack.top() == 2);
    assert(stack.size() == 2);
}

// Queue Tests
TEST(queue_basic) {
    DSA::Queue<int> queue;
    
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    
    assert(queue.front() == 1);
    assert(queue.back() == 3);
    
    queue.dequeue();
    assert(queue.front() == 2);
}

// BST Tests
TEST(bst_insert_search) {
    DSA::BST<int> bst;
    
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    
    assert(bst.search(30));
    assert(bst.search(70));
    assert(!bst.search(100));
    assert(bst.size() == 4);
}

TEST(bst_remove) {
    DSA::BST<int> bst;
    
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    
    bst.remove(30);
    assert(!bst.search(30));
    assert(bst.size() == 2);
}

// Graph Tests
TEST(graph_add_vertices_edges) {
    DSA::Graph<int> graph;
    
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    
    assert(graph.vertexCount() == 4);
}

TEST(graph_bfs_dfs) {
    DSA::Graph<int> graph;
    
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    
    // Just test that BFS and DFS don't crash
    graph.BFS(0);
    graph.DFS(0);
}

// Hash Table Tests
TEST(hashtable_insert_get) {
    DSA::HashTable<std::string, int> table;
    
    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("three", 3);
    
    assert(table.get("one").value() == 1);
    assert(table.get("two").value() == 2);
    assert(!table.get("four").has_value());
}

TEST(hashtable_remove) {
    DSA::HashTable<std::string, int> table;
    
    table.insert("key", 100);
    assert(table.contains("key"));
    
    table.remove("key");
    assert(!table.contains("key"));
}

// Algorithm Tests
TEST(bubblesort) {
    std::vector<int> arr = {5, 2, 8, 1, 9};
    DSA::Algorithms::bubbleSort(arr);
    
    assert(arr == std::vector<int>({1, 2, 5, 8, 9}));
}

TEST(selectionsort) {
    std::vector<int> arr = {5, 2, 8, 1, 9};
    DSA::Algorithms::selectionSort(arr);
    
    assert(arr == std::vector<int>({1, 2, 5, 8, 9}));
}

TEST(linear_search) {
    std::vector<int> arr = {5, 2, 8, 1, 9};
    
    assert(DSA::Algorithms::linearSearch(arr, 8) == 2);
    assert(DSA::Algorithms::linearSearch(arr, 1) == 3);
    assert(DSA::Algorithms::linearSearch(arr, 10) == -1);
}

TEST(binary_search) {
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    assert(DSA::Algorithms::binarySearch(arr, 5) == 4);
    assert(DSA::Algorithms::binarySearch(arr, 1) == 0);
    assert(DSA::Algorithms::binarySearch(arr, 10) == -1);
}

int main() {
    std::cout << "╔════════════════════════════════════╗\n";
    std::cout << "║  Running DSA Library Tests        ║\n";
    std::cout << "╚════════════════════════════════════╝\n\n";
    
    try {
        // Data Structure Tests
        std::cout << "--- Dynamic Array Tests ---\n";
        RUN_TEST(dynamic_array_basic);
        RUN_TEST(dynamic_array_resize);
        
        std::cout << "\n--- Linked List Tests ---\n";
        RUN_TEST(linked_list_basic);
        RUN_TEST(linked_list_contains);
        
        std::cout << "\n--- Stack Tests ---\n";
        RUN_TEST(stack_basic);
        
        std::cout << "\n--- Queue Tests ---\n";
        RUN_TEST(queue_basic);
        
        std::cout << "\n--- BST Tests ---\n";
        RUN_TEST(bst_insert_search);
        RUN_TEST(bst_remove);
        
        std::cout << "\n--- Graph Tests ---\n";
        RUN_TEST(graph_add_vertices_edges);
        RUN_TEST(graph_bfs_dfs);
        
        std::cout << "\n--- Hash Table Tests ---\n";
        RUN_TEST(hashtable_insert_get);
        RUN_TEST(hashtable_remove);
        
        std::cout << "\n--- Algorithm Tests ---\n";
        RUN_TEST(bubblesort);
        RUN_TEST(selectionsort);
        RUN_TEST(linear_search);
        RUN_TEST(binary_search);
        
        std::cout << "\n╔════════════════════════════════════╗\n";
        std::cout << "║  ✓ All Tests Passed!              ║\n";
        std::cout << "╚════════════════════════════════════╝\n";
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n✗ Test failed with exception: " << e.what() << "\n";
        return 1;
    }
}
