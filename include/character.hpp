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

// Make sure it's inside the right namespace so nlohmann::json can find them
namespace dpp {
	// Convert dpp::user to JSON
	inline void to_json(nlohmann::json& j, const dpp::user& user) { // inline scuffed cuz lazy
		j = nlohmann::json {
			{"id", std::to_string(user.id)},
			{"username", user.username}
		};
	}

	// Convert JSON to dpp::user
	inline void from_json(const nlohmann::json& j, dpp::user& user) {
		user.id = dpp::snowflake(j.at("id").get<std::string>());
		user.username = j.at("username").get<std::string>();
	}
}