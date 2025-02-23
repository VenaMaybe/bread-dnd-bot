#include <stack>
#include <vector>
#include "util/random.hpp"
#include "world_gen/dungeon.hpp"

void Dungeon::generate() {
	// Utility Lambda
	auto linkToStartWithReturnPath = [this](Vertex<DungeonNode>* fromNode) -> void {
		// Get the first node, i.e. the entrance
		Vertex<DungeonNode>* entranceNode = nullptr; // could be a random node between entrance and here later
		entranceNode = dungeonGraph.getVertices().at(0).get();

		// Default return path
		ReturnPath returnPath;
		dungeonGraph.addEdge(fromNode, entranceNode, returnPath);

		// Only treasure rooms have return paths ( This will never include treasure rooms at the edge )
		// if (current->getObjAtVert().getNodeType() == NodeType::Treasure1) {
		// 	dungeonGraph.addEdge(current, entranceNode, returnPath);
		// }
	};

	// Manages dungeon expansion
	std::stack<Vertex<DungeonNode>*> nodeStack;

	EntranceNode entrance;
	Vertex<DungeonNode>* entrancePtr = dungeonGraph.addVertex(entrance);
	nodeStack.push(entrancePtr);

	// Some settings
	const int MAX_NODES = 20;
	const int MIN_NODES = 5;
	int nodeCount = 1;

	while (!nodeStack.empty() && nodeCount < MAX_NODES) {
		// Get the current node at the top of the stack
		Vertex<DungeonNode>* current = nodeStack.top();

		// Expand the node by creating a new room
		if (Random::getBernoulliGate(100)) {
			Vertex<DungeonNode>* newNode = nullptr;
			
			// switch statement here later
			if (Random::getBernoulliGate(75)) {
				// 50% chance to just make a combat room
				newNode = dungeonGraph.addVertex(CombatNode());
			} else {
				// Treasure more likely further away from the entrance
				// We might wanna populate treasure after creating the map,
				//		not while creating the map
				newNode = dungeonGraph.addVertex(TreasureNode());
			}

			// Now connect them
			DefaultHallwayPath hallway;
			dungeonGraph.addEdge(current, newNode, hallway);

			

			// Push this onto the stack so it can be expanded
			nodeStack.push(newNode);
			nodeCount++;
		} else {
			////////////////
			// If not at entrance, maybe make a path back
			if (Random::getBernoulliGate(100) && current->getObjAtVert().getNodeType() != NodeType::Entrance1) {
				linkToStartWithReturnPath(current);
			}

			// Backtrack: stop expanding this path

			// Never get rid of the source node, makes MIN_NODES do nothing
			if (current->getObjAtVert().getNodeType() != NodeType::Entrance1) {
				nodeStack.pop();
			}
		}
	}

	linkToStartWithReturnPath(nodeStack.top());

}




/*
void Dungeon::generate() {
	auto* Entrance = dungeonGraph.addVertex(EntranceNode());
	auto* Combat1 = dungeonGraph.addVertex(CombatNode());

	// Maybe have this make copies?
	dungeonGraph.addEdge(Entrance, Combat1, DungeonPath("Hallway"));
}
*/