#include "bot.hpp"
#include "commands/ping_command.hpp"
#include "commands/dice_command.hpp"

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

void Bot::run() {
	bot_.start(dpp::st_wait);
}

// Register all commands
void Bot::registerCommands() {
	// Ping
	ping_command::register_command(bot_);
	// Dice
	dice_command::register_command(bot_);
}

// Set all the callbacks
void Bot::onSlashCommand(const dpp::slashcommand_t& event) {
	const std::string& cmd = event.command.get_command_name();

	if (cmd == ping_command::commandName) {
		ping_command::handlePing(event);
	} else if (cmd == dice_command::commandName) {
		dice_command::handleDice(event);
	}
}