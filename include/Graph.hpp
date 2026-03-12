#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <iostream>

namespace DSA {

/**
 * @brief Simple Graph using adjacency list
 * 
 * Basic graph implementation with BFS and DFS
 */
template<typename T>
class Graph {
private:
    std::unordered_map<T, std::vector<T>> adjacencyList_;
    bool isDirected_;

public:
    Graph(bool directed = false) : isDirected_(directed) {}
    
    // Add a vertex
    void addVertex(const T& vertex) {
        if (adjacencyList_.find(vertex) == adjacencyList_.end()) {
            adjacencyList_[vertex] = std::vector<T>();
        }
    }
    
    // Add an edge
    void addEdge(const T& source, const T& destination) {
        addVertex(source);
        addVertex(destination);
        
        adjacencyList_[source].push_back(destination);
        
        if (!isDirected_) {
            adjacencyList_[destination].push_back(source);
        }
    }
    
    // Breadth-First Search
    void BFS(const T& start) const {
        if (adjacencyList_.find(start) == adjacencyList_.end()) return;
        
        std::unordered_set<T> visited;
        std::queue<T> q;
        
        q.push(start);
        visited.insert(start);
        
        while (!q.empty()) {
            T current = q.front();
            q.pop();
            std::cout << current << " ";
            
            if (adjacencyList_.find(current) != adjacencyList_.end()) {
                for (const auto& neighbor : adjacencyList_.at(current)) {
                    if (visited.find(neighbor) == visited.end()) {
                        visited.insert(neighbor);
                        q.push(neighbor);
                    }
                }
            }
        }
    }
    
    // Depth-First Search
    void DFS(const T& start) const {
        if (adjacencyList_.find(start) == adjacencyList_.end()) return;
        
        std::unordered_set<T> visited;
        std::stack<T> stack;
        
        stack.push(start);
        
        while (!stack.empty()) {
            T current = stack.top();
            stack.pop();
            
            if (visited.find(current) == visited.end()) {
                visited.insert(current);
                std::cout << current << " ";
                
                if (adjacencyList_.find(current) != adjacencyList_.end()) {
                    for (const auto& neighbor : adjacencyList_.at(current)) {
                        if (visited.find(neighbor) == visited.end()) {
                            stack.push(neighbor);
                        }
                    }
                }
            }
        }
    }
    
    // Get number of vertices
    size_t vertexCount() const {
        return adjacencyList_.size();
    }
    
    // Print the graph
    void print() const {
        for (const auto& pair : adjacencyList_) {
            std::cout << pair.first << ": ";
            for (const auto& neighbor : pair.second) {
                std::cout << neighbor << " ";
            }
            std::cout << "\n";
        }
    }
};

} // namespace DSA
