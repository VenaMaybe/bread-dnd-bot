#include "world_gen/dungeonNodePath.hpp"

DungeonNode::DungeonNode(std::string name) 
	: name(name), id(getNextGlobalId()) {}

const std::string& DungeonNode::getName() const { return name; }
const uint64_t& DungeonNode::getId() const { return id; }

EntranceNode::EntranceNode() : DungeonNode("Entrance Room") {}
CombatNode::CombatNode() : DungeonNode("Combat Room") {}

std::ostream& operator<<(std::ostream& os, const DungeonNode& node) {
	os << node.id << "DungeonNode: " << node.name;
	return os;
}

//=====================================
DungeonPath::DungeonPath(std::string name) 
	: name(name), id(getNextGlobalId()) {}

const std::string& DungeonPath::getName() const { return name; }
const uint64_t& DungeonPath::getId() const { return id; }

std::ostream& operator<<(std::ostream& os, const DungeonPath& node) {
	os << node.id << "DungeonPath: " << node.name;
	return os;
}