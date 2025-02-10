#include "commands/character_commands.hpp"
#include "character.hpp"
#include "characterSaves.hpp"

namespace create_character_command {
	void register_command(dpp::cluster& bot) {
		dpp::slashcommand command(commandName, "Create a character", bot.me.id);

		command.add_option(
			dpp::command_option(dpp::co_string, "name", "Your new character's name", true)
		);

		command.add_option(
			dpp::command_option(dpp::co_integer, "health", "Your new character's hp", true)
		);

		bot.global_command_create(command);
	}

	// Create character
	void handle_command(const dpp::slashcommand_t& event) {
		std::cout << "Creating character for " << event.command.usr.global_name << std::endl;

		// Get the user ID
		dpp::snowflake user_id = event.command.usr.id;
		std::string display_name = event.command.usr.global_name;

		// Grab the user input
		std::string name = std::get<std::string>(event.get_parameter("name"));
		int hp = (int)std::get<int64_t>(event.get_parameter("health")); // A quick c-cast

		// Create the character
		Character c;
		c.createdBy = event.command.usr;
		c.characterID = user_id;
		c.name = name;
		c.hp = hp;

		// Right now, we just have the character id and user id be the same (aka 1 char / usr)
		character_map[c.characterID] = c;

		// Save the new character
		save_characters(characterJSONpath);

		event.reply("**" + display_name 
			+ "** created a character named **" 
			+ name + "** (Hp: " + std::to_string(hp) + ")"
		);
	}
}

namespace view_character_command {
	// Handles registration of the command and its options
	void register_command(dpp::cluster& bot) {
		dpp::slashcommand command(commandName, "View your character", bot.me.id);
		bot.global_command_create(command);
	}

	// View character
	void handle_command(const dpp::slashcommand_t& event) {
		std::cout << "View character for " << event.command.usr.global_name;

		// Get the user ID
		dpp::snowflake user_id = event.command.usr.id;
		std::string display_name = event.command.usr.global_name;

		// Check if their character exists
		if (character_map.find(user_id) == character_map.end()) {
			event.reply("You don't have a character yet stupiddd!");
			return;
		}

		// Get their character from their id
		Character c = character_map[user_id];

		// Craft the reply
		std::string replyMessage = "Your character is: **" 
			+ c.name + "** (Hp: " + std::to_string(c.hp) + ")";

		event.reply(replyMessage);
	}
}

namespace edit_character_command {
	// Handles registration of the command and its options
	void register_command(dpp::cluster& bot) {
		dpp::slashcommand command(commandName, "Editing your character", bot.me.id);

		command.add_option(
			dpp::command_option(dpp::co_string, "name", "Your new character's name", false)
		);

		command.add_option(
			dpp::command_option(dpp::co_integer, "health", "Your new character's hp", false)
		);

		bot.global_command_create(command);
	}
	
	// Handles invocation of command
	void handle_command(const dpp::slashcommand_t& event) {
		std::cout << "View character for " << event.command.usr.global_name;

		// Get the user ID
		dpp::snowflake user_id = event.command.usr.id;
		std::string display_name = event.command.usr.global_name;

		// Check if their character exists
		if (character_map.find(user_id) == character_map.end()) {
			event.reply("You don't have a character yet stupiddd!");
			return;
		}

		// Get their character from their id
		Character &c = character_map[user_id];

		// Grab the user input, I hate variants
		auto name_option = event.get_parameter("name");
		auto hp_option = event.get_parameter("health");

		// Check if the variant isn't empty, I hate variants
		if (std::holds_alternative<std::string>(name_option)) {
			c.name = std::get<std::string>(name_option);
		}
		if (std::holds_alternative<int64_t>(hp_option)) {
			c.hp = (int)std::get<int64_t>(hp_option); // A quick c-cast
		}

		// Save the new character
		save_characters(characterJSONpath);

		// Craft the reply
		std::string replyMessage = "Character updated: **" 
			+ c.name + "** (Hp: " + std::to_string(c.hp) + ")";

		event.reply(replyMessage);
	}
}