#pragma once

#include <dpp/dpp.h>
#include <unordered_map>
#include <string>
#include <mutex>

class Bot {
public:
	Bot(const std::string& token);
	void run();

private:
	// The core DPP cluster, main object
	dpp::cluster bot_;

	// Register the commands
	void registerCommands();

	// Callbacks for slash commands
	void onSlashCommand(const dpp::slashcommand_t& event);
};

/*

/ping()
	Pings the bot

/roll(dice, amt)
	Rolls some dnd dice

/create_character(name, health)
	Creates or augments a user's character with a name and health

/edit_character(name, health)
	Edits a character

/view_character()
	Prints character info






	
	
*/