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
 * Prints the maximum flow result in a formatted way
 *
 * @param source Source vertex
 * @param sink Sink vertex
 * @param maxFlow Maximum flow value
 */
void printMaxFlow(int source, int sink, int maxFlow) {
  std::cout << "Maximum flow from vertex " << Color::CYAN << source
            << Color::RESET << " to vertex " << Color::CYAN << sink
            << Color::RESET << ": " << Color::GREEN << maxFlow << Color::RESET
            << std::endl;
}

int main() {
  try {
    // Flag to control visualization generation
    const bool GENERATE_VISUALS = false;

    // Test Bipartite Graph Operations
    std::cout << Color::BOLD << Color::MAGENTA
              << "\n=== Testing Bipartite Graph Operations ===\n"
              << Color::RESET << std::endl;

    // Test Bipartite Graph
    std::cout << Color::CYAN << "\n[Testing Bipartite Graph]" << Color::RESET
              << std::endl;
    Graph<int> bipartiteGraph("inputs/bipartiteGraph.json");
    generateGraphVisualization(bipartiteGraph, "bipartiteGraph",
                               GENERATE_VISUALS);

    std::cout << "Is Bipartite: " << Color::GREEN << std::boolalpha
              << bipartiteGraph.isBipartite() << Color::RESET << std::endl;

    // Test Non-Bipartite Graph
    std::cout << Color::CYAN << "\n[Testing Non-Bipartite Graph]"
              << Color::RESET << std::endl;
    Graph<int> nonBipartiteGraph("inputs/nonBipartiteGraph.json");
    generateGraphVisualization(nonBipartiteGraph, "nonBipartiteGraph",
                               GENERATE_VISUALS);

    std::cout << "Is Bipartite: " << Color::RED << std::boolalpha
              << nonBipartiteGraph.isBipartite() << Color::RESET << std::endl;

    // Test Maximum Flow Operations
    std::cout << Color::BOLD << Color::MAGENTA
              << "\n=== Testing Maximum Flow Operations ===\n"
              << Color::RESET << std::endl;

    // Test Maximum Flow Graph
    std::cout << Color::CYAN << "\n[Testing Maximum Flow Graph]" << Color::RESET
              << std::endl;
    Graph<int> maxFlowGraph("inputs/maxFlowGraph.json");
    generateGraphVisualization(maxFlowGraph, "maxFlowGraph", GENERATE_VISUALS);

    // Test various source-sink pairs
    printMaxFlow(0, 5, maxFlowGraph.getMaxFlow(0, 5));  // Main test
    printMaxFlow(0, 3, maxFlowGraph.getMaxFlow(0, 3));  // Intermediate vertex
    printMaxFlow(2, 5, maxFlowGraph.getMaxFlow(2, 5));  // Different source
    printMaxFlow(0, 0, maxFlowGraph.getMaxFlow(0, 0));  // Same vertex
    printMaxFlow(7, 5, maxFlowGraph.getMaxFlow(7, 5));  // Invalid vertex

  } catch (const std::exception& e) {
    std::cerr << Color::RED << "Error: " << e.what() << Color::RESET
              << std::endl;
    return 1;
  }

  return 0;
}
