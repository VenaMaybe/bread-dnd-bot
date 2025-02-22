#include <stack>
#include <vector>
#include "util/random.hpp"
#include "world_gen/dungeon.hpp"

void Dungeon::generate() {
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

		// 75% chance to create another room
		if (nodeCount < MIN_NODES || Random::getRandomInt(1, 4) < 3){

			Vertex<DungeonNode>* newNode = nullptr;
			
			// switch statement here later
			newNode = dungeonGraph.addVertex(CombatNode());

			// Now connect them
			dungeonGraph.addEdge(current, newNode, DungeonPath("hallway"));

			// If not at entrance, maybe make a path back
			if (nodeCount > 1 && Random::getRandomInt(1, 4) < 2) {
				Vertex<DungeonNode>* randomNode = nullptr;
				randomNode = dungeonGraph.getVertices()[0].get();
				dungeonGraph.addEdge(current, randomNode, DungeonPath("return"));
			}

			// Push this onto the stack so it can be expanded
			nodeStack.push(newNode);
			nodeCount++;
		}
		// 25% chance to not 
		else {
			nodeStack.pop();
		}


	}

}




/*
void Dungeon::generate() {
	auto* Entrance = dungeonGraph.addVertex(EntranceNode());
	auto* Combat1 = dungeonGraph.addVertex(CombatNode());

	// Maybe have this make copies?
	dungeonGraph.addEdge(Entrance, Combat1, DungeonPath("Hallway"));
}
*/