#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <functional>
#include <limits>
#include <algorithm>

namespace DSA {

/**
 * @brief Graph implementation with adjacency list representation
 * 
 * Supports both directed and undirected graphs, weighted and unweighted
 * 
 * Time Complexities:
 * - Add vertex: O(1)
 * - Add edge: O(1)
 * - BFS/DFS: O(V + E)
 * - Dijkstra: O((V + E) log V)
 * 
 * Space Complexity: O(V + E)
 */
template<typename T>
class Graph {
private:
    struct Edge {
        T destination;
        double weight;
        
        Edge(const T& dest, double w = 1.0) 
            : destination(dest), weight(w) {}
    };
    
    std::unordered_map<T, std::vector<Edge>> adjacencyList_;
    bool isDirected_;

public:
    explicit Graph(bool directed = false) : isDirected_(directed) {}
    
    // Add vertex - O(1)
    void addVertex(const T& vertex) {
        if (adjacencyList_.find(vertex) == adjacencyList_.end()) {
            adjacencyList_[vertex] = std::vector<Edge>();
        }
    }
    
    // Add edge - O(1)
    void addEdge(const T& source, const T& destination, double weight = 1.0) {
        addVertex(source);
        addVertex(destination);
        
        adjacencyList_[source].emplace_back(destination, weight);
        
        if (!isDirected_) {
            adjacencyList_[destination].emplace_back(source, weight);
        }
    }
    
    // Remove edge
    void removeEdge(const T& source, const T& destination) {
        auto& edges = adjacencyList_[source];
        edges.erase(
            std::remove_if(edges.begin(), edges.end(),
                [&destination](const Edge& e) { return e.destination == destination; }),
            edges.end()
        );
        
        if (!isDirected_) {
            auto& revEdges = adjacencyList_[destination];
            revEdges.erase(
                std::remove_if(revEdges.begin(), revEdges.end(),
                    [&source](const Edge& e) { return e.destination == source; }),
                revEdges.end()
            );
        }
    }
    
    // Breadth-First Search - O(V + E)
    void BFS(const T& start, std::function<void(const T&)> visit) const {
        if (adjacencyList_.find(start) == adjacencyList_.end()) return;
        
        std::unordered_set<T> visited;
        std::queue<T> q;
        
        q.push(start);
        visited.insert(start);
        
        while (!q.empty()) {
            T current = q.front();
            q.pop();
            visit(current);
            
            if (adjacencyList_.find(current) != adjacencyList_.end()) {
                for (const auto& edge : adjacencyList_.at(current)) {
                    if (visited.find(edge.destination) == visited.end()) {
                        visited.insert(edge.destination);
                        q.push(edge.destination);
                    }
                }
            }
        }
    }
    
    // Depth-First Search - O(V + E)
    void DFS(const T& start, std::function<void(const T&)> visit) const {
        if (adjacencyList_.find(start) == adjacencyList_.end()) return;
        
        std::unordered_set<T> visited;
        DFSHelper(start, visited, visit);
    }
    
private:
    void DFSHelper(const T& vertex, std::unordered_set<T>& visited, 
                   std::function<void(const T&)> visit) const {
        visited.insert(vertex);
        visit(vertex);
        
        if (adjacencyList_.find(vertex) != adjacencyList_.end()) {
            for (const auto& edge : adjacencyList_.at(vertex)) {
                if (visited.find(edge.destination) == visited.end()) {
                    DFSHelper(edge.destination, visited, visit);
                }
            }
        }
    }

public:
    // Iterative DFS
    void DFSIterative(const T& start, std::function<void(const T&)> visit) const {
        if (adjacencyList_.find(start) == adjacencyList_.end()) return;
        
        std::unordered_set<T> visited;
        std::stack<T> stack;
        
        stack.push(start);
        
        while (!stack.empty()) {
            T current = stack.top();
            stack.pop();
            
            if (visited.find(current) == visited.end()) {
                visited.insert(current);
                visit(current);
                
                if (adjacencyList_.find(current) != adjacencyList_.end()) {
                    for (const auto& edge : adjacencyList_.at(current)) {
                        if (visited.find(edge.destination) == visited.end()) {
                            stack.push(edge.destination);
                        }
                    }
                }
            }
        }
    }
    
    // Dijkstra's shortest path - O((V + E) log V)
    std::unordered_map<T, double> dijkstra(const T& start) const {
        std::unordered_map<T, double> distances;
        std::unordered_set<T> visited;
        
        // Initialize distances
        for (const auto& pair : adjacencyList_) {
            distances[pair.first] = std::numeric_limits<double>::infinity();
        }
        distances[start] = 0;
        
        // Priority queue: (distance, vertex)
        using Pair = std::pair<double, T>;
        std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;
        pq.push({0, start});
        
        while (!pq.empty()) {
            T current = pq.top().second;
            double currentDist = pq.top().first;
            pq.pop();
            
            if (visited.find(current) != visited.end()) continue;
            visited.insert(current);
            
            if (adjacencyList_.find(current) != adjacencyList_.end()) {
                for (const auto& edge : adjacencyList_.at(current)) {
                    double newDist = currentDist + edge.weight;
                    if (newDist < distances[edge.destination]) {
                        distances[edge.destination] = newDist;
                        pq.push({newDist, edge.destination});
                    }
                }
            }
        }
        
        return distances;
    }
    
    // Check if graph has cycle (for directed graphs)
    bool hasCycle() const {
        std::unordered_set<T> visited;
        std::unordered_set<T> recStack;
        
        for (const auto& pair : adjacencyList_) {
            if (hasCycleHelper(pair.first, visited, recStack)) {
                return true;
            }
        }
        return false;
    }
    
private:
    bool hasCycleHelper(const T& vertex, std::unordered_set<T>& visited, 
                       std::unordered_set<T>& recStack) const {
        if (recStack.find(vertex) != recStack.end()) return true;
        if (visited.find(vertex) != visited.end()) return false;
        
        visited.insert(vertex);
        recStack.insert(vertex);
        
        if (adjacencyList_.find(vertex) != adjacencyList_.end()) {
            for (const auto& edge : adjacencyList_.at(vertex)) {
                if (hasCycleHelper(edge.destination, visited, recStack)) {
                    return true;
                }
            }
        }
        
        recStack.erase(vertex);
        return false;
    }

public:
    // Utility functions
    size_t vertexCount() const { return adjacencyList_.size(); }
    
    size_t edgeCount() const {
        size_t count = 0;
        for (const auto& pair : adjacencyList_) {
            count += pair.second.size();
        }
        return isDirected_ ? count : count / 2;
    }
    
    bool hasVertex(const T& vertex) const {
        return adjacencyList_.find(vertex) != adjacencyList_.end();
    }
    
    bool hasEdge(const T& source, const T& destination) const {
        if (adjacencyList_.find(source) == adjacencyList_.end()) return false;
        
        const auto& edges = adjacencyList_.at(source);
        return std::any_of(edges.begin(), edges.end(),
            [&destination](const Edge& e) { return e.destination == destination; });
    }
    
    void clear() {
        adjacencyList_.clear();
    }
};

} // namespace DSA
