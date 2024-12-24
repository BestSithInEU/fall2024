// main.cpp
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "Color.hpp"
#include "Graph.cpp"

/**
 * Generates DOT file and converts it to PNG format
 *
 * @param graph The graph to visualize
 * @param graphName Name of the graph for file naming
 * @param generateVisuals Flag to control visualization generation
 * @return bool True if visualization was successful, false otherwise
 */
bool generateGraphVisualization(const Graph<int>& graph,
                                const std::string& graphName,
                                bool generateVisuals) {
  if (!generateVisuals) return true;

  try {
    // Create directories if they don't exist
    std::filesystem::create_directories("outputs/dots");
    std::filesystem::create_directories("outputs/img");

    // Generate DOT file
    std::string dotRepresentation = graph.toDot();
    std::string dotPath = "outputs/dots/" + graphName + ".dot";
    std::string imgPath = "outputs/img/" + graphName + ".png";

    std::ofstream dotFile(dotPath);
    if (!dotFile.is_open()) {
      std::cerr << Color::RED << "Error: Could not create DOT file: " << dotPath
                << Color::RESET << std::endl;
      return false;
    }

    dotFile << dotRepresentation;
    dotFile.close();

    // Convert DOT to PNG
    std::string command = "dot -Tpng " + dotPath + " -o " + imgPath;
    int result = system(command.c_str());

    if (result != 0) {
      std::cerr << Color::YELLOW
                << "Warning: Could not generate PNG visualization. "
                << "Is Graphviz installed?" << Color::RESET << std::endl;
      return false;
    }

    std::cout << Color::GREEN << "Generated visualization: " << imgPath
              << Color::RESET << std::endl;
    return true;

  } catch (const std::exception& e) {
    std::cerr << Color::RED << "Error generating visualization: " << e.what()
              << Color::RESET << std::endl;
    return false;
  }
}

/**
 * Prints the shortest path distances in a formatted table
 *
 * @param graphName Name of the graph being processed
 * @param distances Vector containing shortest path distances
 */
void printDistances(const std::string& graphName,
                    const std::vector<int>& distances) {
  std::cout << Color::CYAN << "\n=== Shortest paths from vertex 0 in "
            << Color::BOLD << graphName << Color::RESET << Color::CYAN
            << " ===" << Color::RESET << std::endl;

  // Print header
  std::cout << std::setw(15) << "Destination" << std::setw(15) << "Distance"
            << std::endl;
  std::cout << std::string(30, '-') << std::endl;

  // Print distances
  for (size_t i = 0; i < distances.size(); ++i) {
    std::cout << std::setw(15) << i << std::setw(15);
    if (distances[i] == std::numeric_limits<int>::max()) {
      std::cout << Color::RED << "∞" << Color::RESET;
    } else {
      std::cout << Color::GREEN << distances[i] << Color::RESET;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

int main() {
  try {
    // Flag to control visualization generation
    const bool GENERATE_VISUALS = false;
    std::vector<int> distances;

    // Test Dijkstra's algorithm
    std::cout << Color::BOLD << Color::MAGENTA
              << "\n[Testing Dijkstra's Algorithm]" << Color::RESET
              << std::endl;
    Graph<int> dijkstraGraph("inputs/dijkstraGraph.json");
    generateGraphVisualization(dijkstraGraph, "dijkstraGraph",
                               GENERATE_VISUALS);

    if (dijkstraGraph.dijkstra(0, distances)) {
      printDistances("dijkstraGraph", distances);
    }

    // Test Bellman-Ford algorithm on normal graph
    std::cout << Color::BOLD << Color::MAGENTA
              << "\n[Testing Bellman-Ford Algorithm]" << Color::RESET
              << std::endl;
    Graph<int> bellmanFordGraph("inputs/bellmanFordGraph.json");
    generateGraphVisualization(bellmanFordGraph, "bellmanFordGraph",
                               GENERATE_VISUALS);

    if (bellmanFordGraph.bellmanFord(0, distances)) {
      printDistances("bellmanFordGraph", distances);
    }

    // Test Bellman-Ford algorithm on graph with negative cycle
    std::cout << Color::BOLD << Color::MAGENTA
              << "\n[Testing Bellman-Ford Algorithm with Negative Cycle]"
              << Color::RESET << std::endl;
    Graph<int> bellmanFordGraphCycle("inputs/bellmanFordGraphCycle.json");
    generateGraphVisualization(bellmanFordGraphCycle, "bellmanFordGraphCycle",
                               GENERATE_VISUALS);

    if (!bellmanFordGraphCycle.bellmanFord(0, distances)) {
      std::cout << Color::RED << Color::BOLD
                << "⚠ Graph contains negative weight cycle!" << Color::RESET
                << std::endl;
    }

  } catch (const std::exception& e) {
    std::cerr << Color::RED << "Error: " << e.what() << Color::RESET
              << std::endl;
    return 1;
  }

  return 0;
}
