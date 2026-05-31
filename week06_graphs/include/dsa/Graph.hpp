#pragma once

#include <cstddef>
#include <stdexcept>

#include "dsa/DynamicArray.hpp"
#include "dsa/Queue.hpp"

namespace dsa {

class Graph {
public:
    Graph(int vertices, bool directed = false)
        : V_(vertices), directed_(directed)
    {
        if (vertices < 0) {
            throw std::invalid_argument("Number of vertices cannot be negative");
        }

        for (int i = 0; i < V_; ++i) {
            adj_.push_back(DynamicArray<int>());
        }
    }

    int vertex_count() const {
        return V_;
    }

    void add_edge(int u, int v) {
        validate_vertex(u);
        validate_vertex(v);

        adj_[u].push_back(v);

        if (!directed_) {
            adj_[v].push_back(u);
        }
    }

    void bfs(int start, void (*visit)(int)) const {
        validate_vertex(start);

        bool* visited = new bool[V_];

        for (int i = 0; i < V_; ++i) {
            visited[i] = false;
        }

        Queue<int> q;

        visited[start] = true;
        q.enqueue(start);

        while (!q.empty()) {
            int current = q.front();
            q.dequeue();

            visit(current);

            for (std::size_t i = 0; i < adj_[current].size(); ++i) {
                int neighbor = adj_[current][i];

                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.enqueue(neighbor);
                }
            }
        }

        delete[] visited;
    }

    void dfs(int start, void (*visit)(int)) const {
        validate_vertex(start);

        bool* visited = new bool[V_];

        for (int i = 0; i < V_; ++i) {
            visited[i] = false;
        }

        dfs_rec(start, visited, visit);

        delete[] visited;
    }

    void bfs_all(void (*visit)(int)) const {
        bool* visited = new bool[V_];

        for (int i = 0; i < V_; ++i) {
            visited[i] = false;
        }

        Queue<int> q;

        for (int start = 0; start < V_; ++start) {

            if (visited[start]) {
                continue;
            }

            visited[start] = true;
            q.enqueue(start);

            while (!q.empty()) {
                int current = q.front();
                q.dequeue();

                visit(current);

                for (std::size_t i = 0; i < adj_[current].size(); ++i) {
                    int neighbor = adj_[current][i];

                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        q.enqueue(neighbor);
                    }
                }
            }
        }

        delete[] visited;
    }

    void dfs_all(void (*visit)(int)) const {
        bool* visited = new bool[V_];

        for (int i = 0; i < V_; ++i) {
            visited[i] = false;
        }

        for (int v = 0; v < V_; ++v) {
            if (!visited[v]) {
                dfs_rec(v, visited, visit);
            }
        }

        delete[] visited;
    }

private:
    void validate_vertex(int v) const {
        if (v < 0 || v >= V_) {
            throw std::out_of_range("Invalid vertex index");
        }
    }

    void dfs_rec(int v, bool* visited, void (*visit)(int)) const {
        visited[v] = true;
        visit(v);

        for (std::size_t i = 0; i < adj_[v].size(); ++i) {
            int neighbor = adj_[v][i];

            if (!visited[neighbor]) {
                dfs_rec(neighbor, visited, visit);
            }
        }
    }

private:
    int V_;
    bool directed_;
    DynamicArray< DynamicArray<int> > adj_;
};

} // namespace dsa