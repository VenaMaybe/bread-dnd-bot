#include "characterSaves.hpp"

#include <json.hpp>
#include <fstream>
#include "character.hpp"

// Save the map of characters
void save_characters(const std::string& filename) {
	std::cout << "save_characters called\n";
	nlohmann::json j;

	// For every character 
	for (auto& [user_id, character] : character_map) {
		std::cout << user_id << "\t" << character.name << std::endl;
		j[std::to_string(user_id)] = {
			{"createdBy", to_json(character.createdBy)},
			{"characterID", character.characterID},
			{"name", character.name},
			{"hp", character.hp}
		};
	}

	// Set an out file stream and dump it
	std::ofstream out(filename);
	out << j.dump(4);
	out.close();
	std::cout << "Done saving characters" << std::endl;
}

// Load the map of characters
void load_characters(const std::string& filename) {
	// Set an input file stream
	std::ifstream in(filename);
	if (!in.is_open()) {
		std::cout << "No characters file exists yet" << std::endl;
		return;
	}

	// Create the json object from the file
	nlohmann::json j;
	in >> j;
	in.close();

	// Repopulate the character map
	for (auto it = j.begin(); it != j.end(); ++it) {
		dpp::snowflake user_id = std::stoull(it.key());
		Character c;

		// Deserialize the fieldssss
		c.createdBy = from_json(it.value().at("createdBy")); // Kinda fucked cuz it's a standalone function
		c.characterID = it.value().at("characterID").get<uint64_t>();
		c.name = it.value().at("name").get<std::string>();
		c.hp = it.value().at("hp").get<int>();

		character_map[user_id] = c;
	}
}