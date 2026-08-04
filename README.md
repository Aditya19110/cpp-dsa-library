# C++ Data Structures & Algorithms Library


Hi there! I'm a fresher C++ developer, and this is my first major project where I decided to build fundamental data structures and algorithms completely from scratch. 

Instead of just relying on standard library functions like `std::vector` or `std::stack`, I wanted to get my hands dirty and figure out exactly how these concepts work **under the hood**. This project is a documentation of my journey learning raw memory management, pointers, and C++ templates.

## 🎯 Why I Built This

- **Mastering the Fundamentals:** I wanted to see exactly how arrays dynamically resize and how linked lists traverse through memory.
- **Interview Preparation:** Building these structures from scratch gave me the confidence to tackle practical technical interview questions.
- **Conquering Pointers:** I wanted to get comfortable working with raw pointers, `new`/`delete` memory allocation, and debugging memory leaks.

## What I've Implemented So Far

### Core Data Structures
- **Dynamic Array**: A resizable array (my own version of `std::vector`!)
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

Here is how I organized my code:

```text
cpp-dsa-library/
├── build.sh               # Simple script I wrote to compile everything
├── CMakeLists.txt         # Alternative build configuration for CMake
├── include/               # The actual logic (Header files with templates)
│   ├── DynamicArray.hpp
│   ├── LinkedList.hpp
│   ├── Stack.hpp
│   ├── Queue.hpp
│   ├── BST.hpp
│   ├── Graph.hpp
│   ├── HashTable.hpp
│   └── Algorithms.hpp
├── src/                   # Main program source files
├── tests/                 # Unit tests I wrote to prove my code works
└── examples/              # Simple examples showing how to use my classes
```

## How to Run My Code

I wanted to make this easy to run without any complex IDE setup. If you are on Mac or Linux (or using Git Bash on Windows), just use my shell script.

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

If you are more comfortable with CMake, you can build it like this:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Simple Code Examples

Here is a quick look at how you can use the data structures I built:

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

## Testing & Correctness

One of my biggest challenges was dealing with memory leaks (I forgot to use `delete[]` quite a few times early on!). To ensure everything works correctly, I wrote 14 automated unit tests. Running `./build/DSA_Tests` executes them all to guarantee the structures are stable.

## Known Limitations

- **For Learning Purposes:** This library was built as a personal learning milestone, not for high-performance production systems. For real-world applications, always use the C++ Standard Template Library (STL).
- **Thread Safety:** I haven't tackled multithreading yet, so these structures are not thread-safe.

## License

This project is open-source and available under the [MIT License](LICENSE). Feel free to use it to aid your own learning journey!
