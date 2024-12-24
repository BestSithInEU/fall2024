#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

// Try multiple possible paths for json.hpp
#if __has_include(<nlohmann/json.hpp>)
#include <nlohmann/json.hpp>
#elif __has_include("../../deps/nlohmann/json.hpp")
#include "../../deps/nlohmann/json.hpp"
#else
#error "Could not find nlohmann/json.hpp. Please run 'make deps' first."
#endif

template <typename T>
class Graph;

template <typename T>
std::ostream &operator<<(std::ostream &os, const Graph<T> &graph);

template <typename T>
class Graph {
 private:
  struct Edge {
    int to;
    T weight;
  };

  std::vector<std::vector<Edge>> adjList;
  int numVertices;

 public:
  explicit Graph(const std::string &filename);
  void addEdge(int from, int to, T weight);
  friend std::ostream &operator<<<>(std::ostream &os, const Graph &graph);
  void readGraphFromFile(const std::string &filename);
  std::string toDot() const;
  bool isBipartite() const;
  T getMaxFlow(int source, int sink) const;

 private:
  void readGraphFromJson(const std::string &filename);
  bool isBipartiteUtil(int start, std::vector<int> &colors) const;
  bool bfs(const std::vector<std::vector<T>> &residualGraph, int source,
           int sink, std::vector<int> &parent) const;
};

#endif /* GRAPH_HPP */
