#include "character.hpp"

// Define the global map here
std::unordered_map<dpp::snowflake, Character> character_map;

// Convert dpp::user to JSON
nlohmann::json to_json(const dpp::user& user) { // inline scuffed cuz lazy
	return nlohmann::json {
		{"id", std::to_string(user.id)},
		{"username", user.username}
	};
}

// Convert JSON to dpp::user
dpp::user from_json(const nlohmann::json& j) {
	dpp::user user;
	user.id = dpp::snowflake(j.at("id").get<std::string>());
	user.username = j.at("username").get<std::string>();
	return user;
}