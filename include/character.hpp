#pragma once

#include <dpp/dpp.h>
#include <unordered_map>
#include <string>

struct Character {
	dpp::user createdBy;
	int64_t characterID;
	std::string name;
	int hp;
};

// Ideally there is only one of these
struct Characters {
	std::unordered_map<dpp::snowflake, Character> characterMap;
};