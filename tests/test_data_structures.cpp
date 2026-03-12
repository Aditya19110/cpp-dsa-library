#include <iostream>
#include <cassert>
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

// AVL Tree Tests
TEST(avl_balance) {
    DSA::AVLTree<int> avl;
    
    // Insert sequential numbers (would be unbalanced in BST)
    for (int i = 1; i <= 15; ++i) {
        avl.insert(i);
    }
    
    // AVL tree should maintain balanced height
    assert(avl.height() <= 4); // log2(15) ≈ 3.9
    assert(avl.size() == 15);
}

TEST(avl_search) {
    DSA::AVLTree<int> avl;
    
    avl.insert(10);
    avl.insert(20);
    avl.insert(5);
    
    assert(avl.search(10));
    assert(avl.search(20));
    assert(!avl.search(15));
}

// Graph Tests
TEST(graph_add_vertices_edges) {
    DSA::Graph<int> graph;
    
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    
    assert(graph.vertexCount() == 4);
    assert(graph.hasVertex(0));
    assert(graph.hasEdge(0, 1));
}

TEST(graph_bfs_dfs) {
    DSA::Graph<int> graph;
    
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    
    std::vector<int> bfs_result;
    graph.BFS(0, [&bfs_result](const int& val) {
        bfs_result.push_back(val);
    });
    
    assert(bfs_result.size() == 4);
    assert(bfs_result[0] == 0);
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
TEST(quicksort) {
    std::vector<int> arr = {5, 2, 8, 1, 9};
    DSA::Algorithms::quickSort(arr);
    
    assert(arr == std::vector<int>({1, 2, 5, 8, 9}));
}

TEST(mergesort) {
    std::vector<int> arr = {5, 2, 8, 1, 9};
    DSA::Algorithms::mergeSort(arr);
    
    assert(arr == std::vector<int>({1, 2, 5, 8, 9}));
}

TEST(binary_search) {
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    assert(DSA::Algorithms::binarySearch(arr, 5) == 4);
    assert(DSA::Algorithms::binarySearch(arr, 1) == 0);
    assert(DSA::Algorithms::binarySearch(arr, 10) == -1);
}

TEST(quickselect) {
    std::vector<int> arr = {7, 10, 4, 3, 20, 15};
    
    int median = DSA::Algorithms::quickSelect(arr, arr.size() / 2);
    assert(median == 7 || median == 10); // 3rd or 4th element when sorted
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
        
        std::cout << "\n--- AVL Tree Tests ---\n";
        RUN_TEST(avl_balance);
        RUN_TEST(avl_search);
        
        std::cout << "\n--- Graph Tests ---\n";
        RUN_TEST(graph_add_vertices_edges);
        RUN_TEST(graph_bfs_dfs);
        
        std::cout << "\n--- Hash Table Tests ---\n";
        RUN_TEST(hashtable_insert_get);
        RUN_TEST(hashtable_remove);
        
        std::cout << "\n--- Algorithm Tests ---\n";
        RUN_TEST(quicksort);
        RUN_TEST(mergesort);
        RUN_TEST(binary_search);
        RUN_TEST(quickselect);
        
        std::cout << "\n╔════════════════════════════════════╗\n";
        std::cout << "║  ✓ All Tests Passed!              ║\n";
        std::cout << "╚════════════════════════════════════╝\n";
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n✗ Test failed with exception: " << e.what() << "\n";
        return 1;
    }
}
