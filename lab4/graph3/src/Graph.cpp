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

/**
 * Helper function for isBipartite that implements the coloring logic using BFS
 *
 * @tparam T The type of the graph's weights
 * @param start Starting vertex for the BFS
 * @param colors Vector storing the colors of vertices
 * @return bool True if the component is bipartite, false otherwise
 */
template <typename T>
bool Graph<T>::isBipartiteUtil(int start, std::vector<int> &colors) const {
  std::queue<int> q;
  q.push(start);
  colors[start] = 0;  // Assign first color to start vertex

  while (!q.empty()) {
    int curr = q.front();
    q.pop();

    // Check all adjacent vertices
    for (const auto &edge : adjList[curr]) {
      int neighbor = edge.to;

      // If neighbor is not colored, color it with opposite color
      if (colors[neighbor] == -1) {
        colors[neighbor] = 1 - colors[curr];
        q.push(neighbor);
      }
      // If neighbor is colored and has same color as current vertex
      else if (colors[neighbor] == colors[curr]) {
        return false;
      }
    }
  }
  return true;
}

/**
 * Finds the maximum flow in a flow network from source to sink using
 * Edmonds-Karp algorithm (Ford-Fulkerson with BFS)
 *
 * @tparam T The type of the graph's weights
 * @param source The source vertex
 * @param sink The sink vertex
 * @return T The maximum flow from source to sink
 */
template <typename T>
T Graph<T>::getMaxFlow(int source, int sink) const {
  if (source == sink) return 0;
  if (source < 0 || sink < 0 || source >= numVertices || sink >= numVertices)
    return 0;

  // Create residual graph
  std::vector<std::vector<T>> residualGraph(numVertices,
                                            std::vector<T>(numVertices, 0));

  // Initialize residual graph with capacities
  for (int i = 0; i < numVertices; i++) {
    for (const auto &edge : adjList[i]) {
      residualGraph[i][edge.to] = edge.weight;
    }
  }

  std::vector<int> parent(numVertices);
  T maxFlow = 0;

  // Augment the flow while there is a path from source to sink
  while (bfs(residualGraph, source, sink, parent)) {
    // Find minimum residual capacity along the path
    T pathFlow = std::numeric_limits<T>::max();
    for (int v = sink; v != source; v = parent[v]) {
      int u = parent[v];
      pathFlow = std::min(pathFlow, residualGraph[u][v]);
    }

    // Update residual capacities and reverse edges
    for (int v = sink; v != source; v = parent[v]) {
      int u = parent[v];
      residualGraph[u][v] -= pathFlow;
      residualGraph[v][u] += pathFlow;  // Add reverse edge for residual graph
    }

    maxFlow += pathFlow;
  }

  return maxFlow;
}

/**
 * Helper function that uses BFS to find a path from source to sink in the
 * residual graph
 *
 * @tparam T The type of the graph's weights
 * @param residualGraph The residual graph
 * @param source The source vertex
 * @param sink The sink vertex
 * @param parent Vector to store the path
 * @return bool True if a path exists, false otherwise
 */
template <typename T>
bool Graph<T>::bfs(const std::vector<std::vector<T>> &residualGraph, int source,
                   int sink, std::vector<int> &parent) const {
  std::vector<bool> visited(numVertices, false);
  std::queue<int> q;

  q.push(source);
  visited[source] = true;
  parent[source] = -1;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v = 0; v < numVertices; v++) {
      if (!visited[v] && residualGraph[u][v] > 0) {
        q.push(v);
        parent[v] = u;
        visited[v] = true;
      }
    }
  }

  return visited[sink];
}

/**
 * Checks if the graph is bipartite (can be colored with two colors such that
 * no adjacent vertices have the same color)
 *
 * @tparam T The type of the graph's weights
 * @return bool True if the graph is bipartite, false otherwise
 */
template <typename T>
bool Graph<T>::isBipartite() const {
  if (numVertices == 0) return true;

  // Colors: -1 = not colored, 0 = first color, 1 = second color
  std::vector<int> colors(numVertices, -1);

  // Check each uncolored vertex as a potential starting point
  for (int i = 0; i < numVertices; i++) {
    if (colors[i] == -1) {
      if (!isBipartiteUtil(i, colors)) {
        return false;
      }
    }
  }
  return true;
}

// Explicit template instantiation
template class Graph<int>;
template class Graph<float>;
template class Graph<double>;
