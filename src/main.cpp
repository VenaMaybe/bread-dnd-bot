// 	Built with DPP
//		> clone https://github.com/brainboxdotcc/DPP
//
//	Installed OpenSSL development files for discord dnd bot
//		> sudo apt install libssl-dev
//	
//	Make sure to build DPP
//		> cmake -B build .
//		> cmake --build build --config Release

#include "bot.h"
#include <cstdlib>

int main() {
	const char* token = std::getenv("DISCORD_TOKEN");
	if (token == nullptr) { throw std::runtime_error("Error: No token found in enviornment!"); }
	std::string token_s(token);

	Bot rat(token_s);
	rat.run();

	return 0;
}

/*	Be sure to run it with the .env exported:
 *		> export $(grep -v '^#' ../.env | xargs) && ./breadDnDBot
 *
 * */