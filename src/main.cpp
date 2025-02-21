// 	Built with DPP
//		> git clone https://github.com/brainboxdotcc/DPP
//
//	Built with nlohmann/json headers
//		> wget -O json.hpp https://github.com/nlohmann/json/releases/latest/download/json.hpp
//
//	Installed OpenSSL development files for discord dnd bot
//		> sudo apt install libssl-dev
//	
//	Make sure to build DPP
//		> cmake -B build .
//		> cmake --build build (or . ) --config Release

// #include "bot.hpp"
// #include "characterSaves.hpp"
// #include <cstdlib>

// int main() {
// 	// Slop to get environmental variable token
// 	const char* token = std::getenv("DISCORD_TOKEN");
// 	if (token == nullptr) { throw std::runtime_error("Error: No token found in enviornment!"); }
// 	std::string token_string(token);

// 	// Load up the characters from the json
// 	load_characters(characterJSONpath);
// 	Bot rat(token_string);
// 	rat.run();

// 	return 0;
// }

#include <iostream>
#include <string>
#include "util/graph.hpp"
#include "util/random.hpp"

int main() {
	// Create a graph where each vertex holds a std::string and each edge holds an int.
	Graph<std::string, int> graph;

	// Add vertices to the graph.
	Vertex<std::string>* vA = graph.addVertex("A");
	Vertex<std::string>* vB = graph.addVertex("B");
	Vertex<std::string>* vC = graph.addVertex("C");
	Vertex<std::string>* vD = graph.addVertex("D");

	// Add edges (with integer weights) between the vertices.
	graph.addEdge(vA, vB, 5);
	graph.addEdge(vB, vC, 10);
	graph.addEdge(vA, vC, 15);
	graph.addEdge(vA, vD);
	graph.addEdge(vA, vB, Random::getRandomInt(200, 400));

	// Print the graph's structure.
	graph.printGraph();

	return 0;
}

/*	Be sure to run it with the .env exported:
 *		> export $(grep -v '^#' ../.env | xargs) && ./breadDnDBot
 *
 * */

/*
	Reminder to self, in vps server:

	>	tmux new -s dndbot
	> 	./build/breadDndBot
	CTRL+B then D
	
	To resume
	>	tmux attach -t dndbot

*/