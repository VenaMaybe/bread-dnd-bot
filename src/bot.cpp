#include "bot.h"
#include "commands/ping_command.h"
#include "commands/dice_command.h"

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
	bot_.global_command_create(
		dpp::slashcommand("ping", "Ping command", bot_.me.id)
	);
	// Dice
	bot_.global_command_create(
		dpp::slashcommand("roll", "Dice command", bot_.me.id)
			.add_option(
				dpp::command_option(dpp::co_integer, "dice", "Type of dice to roll", true)
					.add_choice(dpp::command_option_choice("d4", 	4))
					.add_choice(dpp::command_option_choice("d6", 	6))
					.add_choice(dpp::command_option_choice("d8", 	8))
					.add_choice(dpp::command_option_choice("d10",	10))
					.add_choice(dpp::command_option_choice("d12",	12))
					.add_choice(dpp::command_option_choice("d20", 	20))
					.add_choice(dpp::command_option_choice("d100", 	100))
			)
			.add_option(
				dpp::command_option(dpp::co_integer, "count", "Number of dice to roll", true)
			)
	);
}

// Set all the callbacks
void Bot::onSlashCommand(const dpp::slashcommand_t& event) {
	const std::string& cmd = event.command.get_command_name();

	if (cmd == "ping") {
		handlePing(event);
	} else if (cmd == "roll") {
		handleDice(event);
	}
}