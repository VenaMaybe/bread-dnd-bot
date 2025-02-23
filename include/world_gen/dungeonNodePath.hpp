#pragma once

#include <iostream>
#include <string>
#include <json.hpp> // To add serealization function to_json
using json = nlohmann::json;

inline uint64_t getNextGlobalId() {
	static uint64_t globalId = 0;
	return globalId++;
}

// Types of Nodes or Paths!!!
enum class NodeType {
	Entrance1,
	Combat1,	// Number represents difficult / goodness
	Treasure1
};

class DungeonNode {
public:
	DungeonNode(NodeType type, std::string name, std::string color);
	virtual ~DungeonNode() = default;

	const NodeType& getNodeType() const;
	const std::string& getName() const;
	const std::string& getStringColor() const;
	const uint64_t& getId() const;

protected:
	NodeType type;
	std::string name; // Eg: Treasure Room, Hallway, Battle Room
	std::string string_color;
	uint64_t id;

private:
	// Overload this so we can easily print dungeon node info
	friend std::ostream& operator<<(std::ostream& os, const DungeonNode& node);
};

inline void to_json(json&j, const DungeonNode& node) {
	j = json{
		{"node_type", node.getNodeType()},
		{"color", node.getStringColor()},
		{"name", node.getName()},
		{"id", node.getId()}
	};
}

class EntranceNode : public DungeonNode {
public:
	EntranceNode();
};

class CombatNode : public DungeonNode {
public:
	CombatNode();
};

class TreasureNode : public DungeonNode {
public:
	TreasureNode();
};
	

// Edges in the graph
enum class PathType {
	DefaultHallwayPath,
	ReturnPath
};

class DungeonPath {
public:
	DungeonPath(PathType type, std::string name);
	virtual ~DungeonPath() = default;

	const PathType& getPathType() const;
	const std::string& getName() const;
	const uint64_t& getId() const;

protected:
	PathType type;
	std::string name;
	uint64_t id;

private:
	// Overload this so we can easily print dungeon node info
	friend std::ostream& operator<<(std::ostream& os, const DungeonPath& node);

};

inline void to_json(json&j, const DungeonPath& path) {
	j = json{
		{"path_type", path.getPathType()},
		{"name", path.getName()},
		{"id", path.getId()}
	};
}

class DefaultHallwayPath : public DungeonPath {
public:
	DefaultHallwayPath();
};

class ReturnPath : public DungeonPath {
public:
	ReturnPath();
};