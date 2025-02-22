// 	Built with DPP
//		> git clone https://github.com/brainboxdotcc/DPP
//
//	Built with nlohmann/json headers
//		> wget -O json.hpp https://github.com/nlohmann/json/releases/latest/download/json.hpp
//
//	Installed OpenSSL development files for discord dnd bot
//		> sudo apt install libssl-dev
//	
//	Make sure to build DPP
//		> cmake -B build .
//		> cmake --build build (or . ) --config Release

// #include "bot.hpp"
// #include "characterSaves.hpp"
// #include <cstdlib>

// int main() {
// 	// Slop to get environmental variable token
// 	const char* token = std::getenv("DISCORD_TOKEN");
// 	if (token == nullptr) { throw std::runtime_error("Error: No token found in enviornment!"); }
// 	std::string token_string(token);

// 	// Load up the characters from the json
// 	load_characters(characterJSONpath);
// 	Bot rat(token_string);
// 	rat.run();

// 	return 0;
// }

/*	Be sure to run it with the .env exported:
 *		> export $(grep -v '^#' ../.env | xargs) && ./breadDnDBot
 *
 * */

/*
	Reminder to self, in vps server:

	>	tmux new -s dndbot
	> 	./build/breadDndBot
	CTRL+B then D
	
	To resume
	>	tmux attach -t dndbot

*/