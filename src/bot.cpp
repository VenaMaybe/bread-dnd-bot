#include "bot.hpp"
#include "commands/ping_command.hpp"
#include "commands/dice_command.hpp"
#include "commands/character_commands.hpp"

// Create the bot
Bot::Bot(const std::string& token)
	: bot_(token) {
	
	// Log to console
	bot_.on_log(dpp::utility::cout_logger());

	bot_.on_ready([this](const dpp::ready_t& event) {
		if (dpp::run_once<struct register_bot_commands>()) {
			this->registerCommands(); // all our tasty commands
		}
	});

	// When fully ready
	bot_.on_slashcommand([this](const dpp::slashcommand_t& event) {
		this->onSlashCommand(event);
	});
}

// Start the bot
void Bot::run() {
	bot_.start(dpp::st_wait);
}

// Register all commands
void Bot::registerCommands() {
	ping_command::register_command(bot_);
	dice_command::register_command(bot_);
	create_character_command::register_command(bot_);
	view_character_command::register_command(bot_);
	edit_character_command::register_command(bot_);
}

// Set all the callbacks
void Bot::onSlashCommand(const dpp::slashcommand_t& event) {
	const std::string& cmd = event.command.get_command_name();

	if (cmd == ping_command::commandName) {
		ping_command::handle_command(event);
	} else if (cmd == dice_command::commandName) {
		dice_command::handle_command(event);
	} else if (cmd == create_character_command::commandName) {
		create_character_command::handle_command(event);
	} else if (cmd == view_character_command::commandName) {
		view_character_command::handle_command(event);
	} else if (cmd == edit_character_command::commandName) {
		edit_character_command::handle_command(event);
	}
}