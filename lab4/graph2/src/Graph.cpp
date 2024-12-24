#include "Graph.hpp"

// Try multiple possible paths for json.hpp
#if __has_include(<nlohmann/json.hpp>)
#include <nlohmann/json.hpp>
#elif __has_include("../../deps/nlohmann/json.hpp")
#include "../../deps/nlohmann/json.hpp"
#endif

/**
 * The Graph constructor reads a graph from a file.
 *
 * @param filename The filename parameter is a string that
 * represents the name of the file from which the graph
 * data will be read.
 */
template <typename T>
Graph<T>::Graph(const std::string &filename) {
  readGraphFromJson(filename);
}

/**
 * The function adds an edge between two vertices in a graph with a specified
 * weight.
 *
 * @param from The index of the vertex from which the edge starts.
 * @param to The "to" parameter represents the destination vertex of the edge
 * being added.
 * @param weight The weight parameter represents the weight or cost associated
 * with the edge between the "from" vertex and the "to" vertex. It can be any
 * value that represents the cost or weight of the edge, such as a numerical
 * value or an object that encapsulates the weight information.
 */
template <typename T>
void Graph<T>::addEdge(int from, int to, T weight) {
  adjList[from].push_back({to, weight});
}

/**
 * The function overloads the << operator to print the adjacency list
 * representation of a graph.
 *
 * @return a reference to the `std::ostream` object `os`.
 */
template <typename T>
std::ostream &operator<<(std::ostream &os, const Graph<T> &graph) {
  os << "Graph Representation (Adjacency List):\n";
  for (int i = 0; i < graph.numVertices; ++i) {
    os << "Vertex " << i << " connects to: ";
    for (const auto &edge : graph.adjList[i]) {
      os << "[Vertex " << edge.to << " with weight " << edge.weight << "] ";
    }
    if (graph.adjList[i].empty()) {
      os << "No connections";
    }
    os << "\n";
  }
  return os;
}

/**
 * The function reads a graph from a file and populates the adjacency list with
 * the graph data.
 *
 * @param filename The filename parameter is a string that represents the name
 * of the file from which the graph data will be read.
 */
template <typename T>
void Graph<T>::readGraphFromJson(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file: " + filename);
  }

  nlohmann::json json;
  file >> json;

  numVertices = json["vertices"];
  adjList.resize(numVertices);

  for (const auto &edge : json["edges"]) {
    int from = edge["from"];
    int to = edge["to"];
    T weight = edge["weight"];
    addEdge(from, to, weight);
  }
}

template <typename T>
std::string Graph<T>::toDot() const {
  std::ostringstream dot;
  dot << "digraph G {\n";  // Use "digraph" for directed graphs
  for (int i = 0; i < numVertices; ++i) {
    for (const auto &edge : adjList[i]) {
      dot << "  " << i << " -> " << edge.to << " [label=" << edge.weight
          << "];\n";
    }
  }
  dot << "}\n";
  return dot.str();
}

template <typename T>
bool Graph<T>::topologicalSortUtil(int v, std::vector<bool> &visited,
                                   std::vector<int> &result,
                                   std::vector<bool> &recStack) {
  visited[v] = true;
  recStack[v] = true;

  for (const auto &edge : adjList[v]) {
    if (!visited[edge.to] &&
        topologicalSortUtil(edge.to, visited, result, recStack))
      return true;
    else if (recStack[edge.to])
      return true;
  }

  recStack[v] = false;
  result.push_back(v);
  return false;
}

template <typename T>
bool Graph<T>::topologicalSort() {
  std::vector<int> result;
  std::vector<bool> visited(numVertices, false);
  std::vector<bool> recStack(numVertices, false);

  for (int i = 0; i < numVertices; i++)
    if (!visited[i])
      if (topologicalSortUtil(i, visited, result, recStack)) return false;

  for (auto it = result.rbegin(); it != result.rend(); ++it) {
    std::cout << *it << " ";
  }
  return true;
}

template <typename T>
bool Graph<T>::isDAGUtil(int v, std::vector<bool> &visited,
                         std::vector<bool> &recStack) {
  if (!visited[v]) {
    visited[v] = true;
    recStack[v] = true;

    for (const auto &edge : adjList[v]) {
      if (!visited[edge.to] && isDAGUtil(edge.to, visited, recStack))
        return true;
      else if (recStack[edge.to])
        return true;
    }
  }
  recStack[v] = false;
  return false;
}

template <typename T>
bool Graph<T>::isDAG() {
  std::vector<bool> visited(numVertices, false);
  std::vector<bool> recStack(numVertices, false);

  for (int i = 0; i < numVertices; i++)
    if (isDAGUtil(i, visited, recStack)) return false;

  return true;
}

// Explicit template instantiation
template class Graph<int>;
template class Graph<float>;
template class Graph<double>;
