#pragma once

#include <json.hpp>
#include <dpp/dpp.h>
#include <unordered_map>
#include <string>

// Holds the character
struct Character {
	dpp::user createdBy;
	int64_t characterID;
	std::string name;
	int hp;
};

// Ideally there is only one of these, declared but not defined
extern std::unordered_map<dpp::snowflake, Character> character_map;

// Convert dpp::user to JSON
nlohmann::json to_json(const dpp::user& user);

// Convert JSON to dpp::user
dpp::user from_json(const nlohmann::json& j);