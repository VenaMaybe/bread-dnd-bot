#include <iostream>
#include <string>
#include "util/graph.hpp"
#include "util/random.hpp"

#include "world_gen/dungeon.hpp"

int main() {
	// // Create a graph where each vertex holds a std::string and each edge holds an int.
	// Graph<std::string, int> graph;

	// // Add vertices to the graph.
	// Vertex<std::string>* vA = graph.addVertex("A");
	// Vertex<std::string>* vB = graph.addVertex("B");
	// Vertex<std::string>* vC = graph.addVertex("C");
	// Vertex<std::string>* vD = graph.addVertex("D");

	// // Add edges (with integer weights) between the vertices.
	// graph.addEdge(vA, vB, 5);
	// graph.addEdge(vB, vC, 10);
	// graph.addEdge(vA, vC, 15);
	// graph.addEdge(vA, vD);
	// graph.addEdge(vA, vB, Random::getRandomInt(200, 400));

	// // Print the graph's structure.
	// graph.printGraph();

	Dungeon d1;

	d1.generate();

//	d1.dungeonGraph.printGraph();

	d1.dungeonGraph.exploreGraphToJson("graph.json");
	d1.dungeonGraph.runPythonVisualization();

	return 0;
}