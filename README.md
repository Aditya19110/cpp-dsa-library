# C++ Data Structures & Algorithms Library

> **📚 A Learning Project by a Fresher C++ Developer**
> 
> This is my first major C++ project where I implemented fundamental data structures and algorithms from scratch. I built this to understand how these concepts work internally, not just to use library functions.

## 🎯 Why I Built This

- To learn how data structures actually work "under the hood"
- Practice implementing algorithms I learned in college
- Build something to show in interviews
- Get comfortable with C++ pointers and memory management

## Features

### Data Structures
- **Dynamic Array** - A resizable array (like vector)
- **Linked List** - Singly and doubly linked lists
- **Stack** - LIFO data structure
- **Queue** - FIFO data structure
- **Binary Search Tree (BST)** - Tree with ordered elements
- **Graph** - Basic graph with BFS and DFS
- **Hash Table** - Key-value storage

### Algorithms
- **Sorting**: Bubble Sort, Selection Sort
- **Searching**: Linear Search, Binary Search
- **Graph Traversal**: BFS, DFS

### What I Learned
- Manual memory management with new/delete
- Template programming basics
- Time complexity (O notation)
- Debugging memory leaks
- Writing test cases

## Project Structure

```
DSA-Project_CustomCPP lib/
├── build.sh               # Simple build script
├── README.md              # This file
├── include/               # Header files
│   ├── DynamicArray.hpp
│   ├── LinkedList.hpp
│   ├── Stack.hpp
│   ├── Queue.hpp
│   ├── BST.hpp
│   ├── Graph.hpp
│   ├── HashTable.hpp
│   └── Algorithms.hpp
├── src/                   # Source files
│   └── main.cpp
├── tests/                 # Test cases
│   └── test_data_structures.cpp
└── examples/              # Usage examples
    └── usage_examples.cpp
```

## Building the Project

### Simple Method (Using Shell Script)
```bash
# Make the build script executable
chmod +x build.sh

# Build everything
./build.sh

# Run the programs
./build/DSA_Library
./build/DSA_Tests
```

### Using CMake (Optional)
```bash
mkdir build && cd build
cmake ..
cmake --build .
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
## Usage Examples

### Dynamic Array
```cpp
#include "DynamicArray.hpp"

DSA::DynamicArray<int> arr;
arr.push_back(10);
arr.push_back(20);
std::cout << arr[0] << std::endl; // 10
```

### Binary Search Tree
```cpp
#include "BST.hpp"

DSA::BST<int> tree;
tree.insert(10);
tree.insert(20);
tree.insert(5);
bool found = tree.search(10); // true
```

### Graph with BFS
```cpp
#include "Graph.hpp"

DSA::Graph<int> graph;
graph.addEdge(0, 1);
graph.addEdge(0, 2);
graph.BFS(0); // Prints: 0 1 2
```

### Sorting
```cpp
#include "Algorithms.hpp"

std::vector<int> data = {5, 2, 8, 1, 9};
DSA::Algorithms::bubbleSort(data);
// data is now: {1, 2, 5, 8, 9}
```

## 📖 My Learning Journey

- **Week 1-2:** Built Dynamic Array - learned about pointers and memory allocation
- **Week 3-4:** Implemented LinkedList and Stack - understood the difference between array-based and pointer-based structures
- **Week 5-6:** Created BST - recursion finally clicked for me!
- **Week 7:** Added Graph with BFS/DFS - graph traversal was tricky
- **Week 8:** Implemented sorting algorithms and hash table

Biggest challenges:
- Debugging memory leaks (forgot to delete[] many times!)
- Understanding recursion for tree traversals
- Getting template syntax right

## ✅ Test Coverage

All data structures have test cases to verify correctness:
- 14 unit tests covering all major operations
- Tests run automatically on build
- Run tests: `./build/DSA_Tests`

## 🚀 What's Next

Things I want to add as I learn more:
- [ ] More sorting algorithms (Quick Sort, Merge Sort)
- [ ] AVL Tree (self-balancing)
- [ ] Graph algorithms (Dijkstra's shortest path)
- [ ] Better error handling
- [ ] Performance benchmarks

## ⚠️ Known Limitations

- This is a learning project, not production-ready
- Some edge cases might not be handled
- Focused on correctness over performance
- Not thread-safe

## License

MIT License - Feel free to use for learning
