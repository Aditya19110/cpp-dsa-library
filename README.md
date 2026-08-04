# C++ Data Structures & Algorithms Library

Welcome! If you are a beginner (or "fresher") in C++ and want to understand how data structures and algorithms actually work under the hood, you are in the right place. 

This is a learning-focused project where fundamental data structures and algorithms have been built from scratch. Instead of just using standard libraries like `std::vector` or `std::stack`, this repository shows you exactly how memory management, pointers, and templates bring these concepts to life.

## Why This Project Exists

- **Learn the "Under the Hood" Mechanics:** See exactly how arrays resize and how linked lists traverse memory.
- **Interview Preparation:** Practical implementation of concepts frequently asked in technical interviews.
- **Master C++ Fundamentals:** Get comfortable with raw pointers, `new`/`delete` memory management, and template programming.

## What is Included?

### Core Data Structures
- **Dynamic Array**: A resizable array (similar to `std::vector`)
- **Linked List**: Classic Singly and Doubly Linked Lists
- **Stack**: Last-In-First-Out (LIFO) structure
- **Queue**: First-In-First-Out (FIFO) structure
- **Binary Search Tree (BST)**: Tree structure with ordered elements
- **Graph**: Basic graph representation with BFS (Breadth-First Search) and DFS (Depth-First Search)
- **Hash Table**: Basic Key-Value storage mechanism

### Algorithms
- **Sorting**: Bubble Sort, Selection Sort
- **Searching**: Linear Search, Binary Search
- **Graph Traversal**: BFS, DFS

## Project Structure

```text
cpp-dsa-library/
├── build.sh               # Simple script to compile everything automatically
├── CMakeLists.txt         # Alternative build configuration for CMake users
├── include/               # The actual logic (Header files)
│   ├── DynamicArray.hpp
│   ├── LinkedList.hpp
│   ├── Stack.hpp
│   ├── Queue.hpp
│   ├── BST.hpp
│   ├── Graph.hpp
│   ├── HashTable.hpp
│   └── Algorithms.hpp
├── src/                   # Main program source files
├── tests/                 # Unit tests to prove the code works!
└── examples/              # Simple examples showing how to use each structure
```

## How to Run This Code

You don't need any complex IDE setup to run this. If you are on Mac or Linux (or using Git Bash on Windows), just use the provided script.

### 1. The Simple Way (Using the Shell Script)

Open your terminal, go to the project folder, and run:

```bash
# Make the build script executable (you only need to do this once)
chmod +x build.sh

# Run the build script
./build.sh
```

Once it compiles, you can run the generated programs:
```bash
# Run the main library executable
./build/DSA_Library

# Run the test suite to verify everything works
./build/DSA_Tests

# Run the basic usage examples
./build/DSA_Examples
```

### 2. The Standard Way (Using CMake)

If you are familiar with CMake, you can build it like this:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Simple Code Examples

Here is how easy it is to use the data structures from this library in your own C++ code:

### 1. Dynamic Array
```cpp
#include "DynamicArray.hpp"
#include <iostream>

int main() {
    DSA::DynamicArray<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    
    std::cout << "First element is: " << arr[0] << std::endl; // Outputs: 10
    return 0;
}
```

### 2. Binary Search Tree (BST)
```cpp
#include "BST.hpp"

int main() {
    DSA::BST<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    
    bool found = tree.search(10); // Returns true
    return 0;
}
```

### 3. Graph with BFS Traversal
```cpp
#include "Graph.hpp"

int main() {
    DSA::Graph<int> graph;
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    
    // Prints the breadth-first search path starting from node 0
    graph.BFS(0); 
    return 0;
}
```

## Testing

This project includes 14 automated unit tests to guarantee that operations (like inserting, deleting, and searching) behave correctly without memory leaks. Running `./build/DSA_Tests` will execute them all.

## Known Limitations

- **For Learning Only:** This library is optimized for learning and readability, not for high-performance production systems. For real-world applications, always prefer the C++ Standard Template Library (STL).
- **Thread Safety:** These data structures are not thread-safe.

## License

This project is open-source and available under the [MIT License](LICENSE).
