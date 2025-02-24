#include <stack>
#include <vector>
#include "util/random.hpp"
#include "util/print_stack.hpp"
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
	/*	Every node on the stack is a candidate for further extension
	 * 
	 *	The top node is actively being considered for expansion
	 *
	 * 	Popped nodes are dead ends
	 *
	 * */
	std::stack<Vertex<DungeonNode>*> nodeStack;

	EntranceNode entrance;
	Vertex<DungeonNode>* entrancePtr = dungeonGraph.addVertex(entrance);
	nodeStack.push(entrancePtr);

	// Some settings
	const int MAX_NODES = 20;
	const int MIN_NODES = 5;
	int minimumNodesBeforeSplit = Random::getRandomInt(2, 4);

	// Some counts
	int nodeCount = 1;
	int expansionDepth = 0;

	// Inital state
	printStack(nodeStack);

	while (!nodeStack.empty() && nodeCount < MAX_NODES) {
		// Get the current node at the top of the stack
		Vertex<DungeonNode>* current = nodeStack.top();

		// Get the node type for the current node
		const NodeType& currentNodeType = current->getObjAtVert().getNodeType();

		// Decide whether or not a node should be expanded
		bool shouldSplit; 

		// Check whether or not to expand again
		if (expansionDepth < minimumNodesBeforeSplit) {
			// Definitely true
			shouldSplit = false;
		} else {
			// Might be false
			shouldSplit = Random::getBernoulliGate(50); // prob of splitting
		}

		// Expand the node by creating a new room if shouldn't split
		if (!shouldSplit) {
			Vertex<DungeonNode>* newNode = nullptr;
			
			// Determine room type
			if (Random::getBernoulliGate(75)) {
				// 50% chance to just make a combat room
				newNode = dungeonGraph.addVertex(CombatNode());
			} else {
				// Treasure more likely further away from the entrance
				// We might wanna populate treasure after creating the map,
				//		not while creating the map
				newNode = dungeonGraph.addVertex(TreasureNode());
			}

			// Connect the current node to the new node via a hallway
			DefaultHallwayPath hallway;
			dungeonGraph.addEdge(current, newNode, hallway);
			
			// Add the expansion depth
			expansionDepth++;
			
			// Push this onto the stack so it can be expanded
			nodeStack.push(newNode);
			nodeCount++;
		}

		// If we decide not to expand, backtrack
		if (shouldSplit) {

			// Decide whether or not to create a return path
			bool shouldReturnToEntrance = Random::getBernoulliGate(100);

			// If not at entrance, make a path back
			if (shouldReturnToEntrance && currentNodeType != NodeType::Entrance1) {
				linkToStartWithReturnPath(current);
			}

			// Backtrack: stop expanding this path

			// Never get rid of the source node, makes MIN_NODES do nothing
			if (currentNodeType != NodeType::Entrance1) {
				// How far back should we backtrack
				for (int i = 0; i < minimumNodesBeforeSplit; i++) {
					nodeStack.pop();
				}

				// Decide on a new minimum distance before potentially splitting
				minimumNodesBeforeSplit = Random::getRandomInt(2, 4);
			}

			// We've split
			expansionDepth = 0;
		}
		printStack(nodeStack);
		std::cout << "expansionDepth: " << expansionDepth << std::endl;
	}

	// Connect the very last node ot the start
//	linkToStartWithReturnPath(nodeStack.top());

}




/*
void Dungeon::generate() {
	auto* Entrance = dungeonGraph.addVertex(EntranceNode());
	auto* Combat1 = dungeonGraph.addVertex(CombatNode());

	// Maybe have this make copies?
	dungeonGraph.addEdge(Entrance, Combat1, DungeonPath("Hallway"));
}
*/