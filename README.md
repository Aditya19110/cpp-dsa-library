# Custom C++ Data Structures & Algorithms Library

> **📚 A Learning Project by a Fresher C++ Developer**
> 
> This project was built from scratch to deeply understand how data structures and algorithms work internally, going beyond just using STL containers. As a fresher developer, I implemented each structure step-by-step, learning modern C++ features along the way.

## 🎯 Learning Objectives

- Understand time/space complexity through implementation
- Learn modern C++ features (smart pointers, templates, move semantics)
- Practice writing clean, documented code
- Build a portfolio project demonstrating CS fundamentals

## Features

### Data Structures
- **Dynamic Array** - Template-based resizable array with automatic memory management
- **Linked List** - Singly and doubly linked list implementations
- **Stack** - LIFO data structure with push/pop operations
- **Queue** - FIFO data structure with enqueue/dequeue operations
- **Binary Search Tree (BST)** - Ordered tree structure with O(log n) search
- **AVL Tree** - Self-balancing BST with guaranteed O(log n) operations
- **Graph** - Adjacency list and matrix representations
- **Hash Table** - Efficient key-value storage with collision handling

### Algorithms
- **Sorting**: Quick Sort, Merge Sort, Heap Sort
- **Searching**: Binary Search, DFS, BFS
- **Graph Algorithms**: Dijkstra's, Topological Sort

### Modern C++ Features
- Template metaprogramming for generic implementations
- Smart pointers (unique_ptr, shared_ptr) for automatic memory management
- Move semantics for efficient resource management
- RAII principles throughout
- STL integration and iterators
- Exception safety guarantees

## Project Structure

```
DSA-Project_CustomCPP lib/
├── CMakeLists.txt          # Build configuration
├── README.md               # This file
├── include/                # Header files
│   ├── DynamicArray.hpp
│   ├── LinkedList.hpp
│   ├── Stack.hpp
│   ├── Queue.hpp
│   ├── BST.hpp
│   ├── AVLTree.hpp
│   ├── Graph.hpp
│   ├── HashTable.hpp
│   └── Algorithms.hpp
├── src/                    # Source files
│   └── main.cpp
├── tests/                  # Unit tests
│   └── test_data_structures.cpp
└── examples/               # Usage examples
    └── usage_examples.cpp
```

## Building the Project

### Requirements
- C++17 or later compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.10 or later

### Build Instructions

```bash
# Create build directory
mkdir build && cd build

# Configure
cmake ..

# Build
cmake --build .

# Run
./DSA_Library
```

## Usage Examples

### Dynamic Array
```cpp
#include "DynamicArray.hpp"

DSA::DynamicArray<int> arr;
arr.push_back(10);
arr.push_back(20);
std::cout << arr[0] << std::endl; // 10
```

### AVL Tree
```cpp
#include "AVLTree.hpp"

DSA::AVLTree<int> tree;
tree.insert(10);
tree.insert(20);
tree.insert(5);
bool found = tree.search(10); // true
```

### Graph with BFS
```cpp
#include "Graph.hpp"

DSA::Graph<int> graph(5);
graph.addEdge(0, 1);
graph.addEdge(0, 2);
graph.BFS(0); // Breadth-first traversal
```

## Complexity Analysis

All implementations include detailed time and space complexity analysis in comments.

## License

MIT License - Feel free to use for learning and projects

## 📖 Learning Journey

This project represents my journey learning C++ and data structures:
- **Phase 1:** Started with basic structures (Array, LinkedList, Stack, Queue)
- **Phase 2:** Moved to trees (BST, then self-balancing AVL)
- **Phase 3:** Implemented graphs and hash tables
- **Phase 4:** Added classic algorithms and comprehensive testing

See [LEARNING_JOURNEY.md](LEARNING_JOURNEY.md) for detailed progression and lessons learned.

## 🎓 What I Learned

- **Memory Management:** Smart pointers prevent leaks without manual delete
- **Templates:** Write generic code that works with any type
- **Complexity Analysis:** Understand why certain operations are O(1) vs O(n)
- **Trade-offs:** Each structure has pros/cons for different use cases
- **Testing:** How to verify code correctness systematically

## 🚀 Future Improvements

As I continue learning, I plan to add:
- [ ] Red-Black Tree implementation
- [ ] Trie (Prefix Tree) for string operations
- [ ] More graph algorithms (Kruskal's, Prim's)
- [ ] Performance benchmarking suite
- [ ] Thread-safe versions using mutexes

## Author

Fresher C++ Developer building this as a learning project to master data structures and modern C++ practices
