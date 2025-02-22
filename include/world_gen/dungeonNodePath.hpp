#pragma once

#include <iostream>
#include <string>
#include <json.hpp> // To add serealization function to_json
using json = nlohmann::json;

inline uint64_t getNextGlobalId() {
	static uint64_t globalId = 0;
	return globalId++;
}

class DungeonNode {
public:
	DungeonNode(std::string name);
	virtual ~DungeonNode() = default;

	const std::string& getName() const;
	const uint64_t& getId() const;

protected:
	std::string name; // Eg: Treasure Room, Hallway, Battle Room
	uint64_t id;

private:
	// Overload this so we can easily print dungeon node info
	friend std::ostream& operator<<(std::ostream& os, const DungeonNode& node);
};

inline void to_json(json&j, const DungeonNode& node) {
	j = json{
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

// Edges in the graph
class DungeonPath {
public:
	DungeonPath(std::string name);
	virtual ~DungeonPath() = default;

	const std::string& getName() const;
	const uint64_t& getId() const;

protected:
	std::string name;
	uint64_t id;

private:
	// Overload this so we can easily print dungeon node info
	friend std::ostream& operator<<(std::ostream& os, const DungeonPath& node);

};

inline void to_json(json&j, const DungeonPath& path) {
	j = json{
		{"name", path.getName()},
		{"id", path.getId()}
	};
}
