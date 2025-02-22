#pragma once

#include "util/graph.hpp"
#include "world_gen/dungeonNodePath.hpp"


// Graph of nodes and edges
class Dungeon {
public:
	void generate();

	Graph<DungeonNode, DungeonPath> dungeonGraph;

};



