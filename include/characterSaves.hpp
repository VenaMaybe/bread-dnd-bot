#pragma once

#include <string>

// The path to the json file where we map to
inline constexpr const char* characterJSONpath = "../characters.json";

// Save the map of characters
void save_characters(const std::string& filename);

// Load the map of characters
void load_characters(const std::string& filename);