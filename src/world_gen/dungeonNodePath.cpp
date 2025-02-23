#include "world_gen/dungeonNodePath.hpp"

DungeonNode::DungeonNode(NodeType type, std::string name, std::string color) 
	: type(type), name(name), string_color(color), id(getNextGlobalId()) {}

const NodeType& DungeonNode::getNodeType() const { return type; }
const std::string& DungeonNode::getName() const { return name; }
const std::string& DungeonNode::getStringColor() const { return string_color; }
const uint64_t& DungeonNode::getId() const { return id; }

using NT = NodeType;
EntranceNode::EntranceNode() : DungeonNode(NT::Entrance1, "Entrance Room", "gold") {}
CombatNode::CombatNode() : DungeonNode(NT::Combat1, "Combat Room", "lightcoral") {}
TreasureNode::TreasureNode() : DungeonNode(NT::Treasure1, "Treasure Room!!!", "lightblue") {}

std::ostream& operator<<(std::ostream& os, const DungeonNode& node) {
	os << node.id << "DungeonNode: " << node.name;
	return os;
}

//=====================================
DungeonPath::DungeonPath(PathType type, std::string name) 
	: type(type), name(name), id(getNextGlobalId()) {}

const PathType& DungeonPath::getPathType() const { return type; }
const std::string& DungeonPath::getName() const { return name; }
const uint64_t& DungeonPath::getId() const { return id; }

std::ostream& operator<<(std::ostream& os, const DungeonPath& node) {
	os << node.id << "DungeonPath: " << node.name;
	return os;
}

using PT = PathType;
DefaultHallwayPath::DefaultHallwayPath() : DungeonPath(PT::DefaultHallwayPath, "Hallway") {}
ReturnPath::ReturnPath() : DungeonPath(PT::ReturnPath, "Return") {}