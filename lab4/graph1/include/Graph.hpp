#ifndef D735F8E8_8C27_4C0D_A975_B917F625D76B
#define D735F8E8_8C27_4C0D_A975_B917F625D76B

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
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
  bool bellmanFord(int src, std::vector<T> &distances);
  bool dijkstra(int src, std::vector<T> &distances);

 private:
  void readGraphFromJson(const std::string &filename);
};

#endif /* D735F8E8_8C27_4C0D_A975_B917F625D76B */
