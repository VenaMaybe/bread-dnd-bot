#include "commands/dice_command.hpp"
#include <random>

namespace dice_command {
	void register_command(dpp::cluster& bot) {
		dpp::slashcommand command(commandName, "Roll some dice", bot.me.id);

		command.add_option(
			dpp::command_option(dpp::co_integer, "dice", "Type of dice to roll", true)
				.add_choice(dpp::command_option_choice("d4", 	4))
				.add_choice(dpp::command_option_choice("d6", 	6))
				.add_choice(dpp::command_option_choice("d8", 	8))
				.add_choice(dpp::command_option_choice("d10",	10))
				.add_choice(dpp::command_option_choice("d12",	12))
				.add_choice(dpp::command_option_choice("d20", 	20))
				.add_choice(dpp::command_option_choice("d100", 	100))
		);

		command.add_option(
			dpp::command_option(dpp::co_integer, "count", "Number of dice to roll", true)
		);

		bot.global_command_create(command);
	}

	void handleDice(const dpp::slashcommand_t& event) {
		// Grab the user input
		int64_t diceValue = std::get<int64_t>(event.get_parameter("dice"));
		int64_t diceCount = std::get<int64_t>(event.get_parameter("count"));

		// Debug output
		std::cout << "[INFO] diceValue = " << diceValue << ", diceCount = " << diceCount << std::endl;

		// Create the random device
		static std::random_device rd;
		static std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(1, diceValue);

		std::string rolls;
		int total = 0; 
		for (int i = 0; i < diceCount; ++i) {
			int roll = dist(gen);
			total += roll;

			if (i < (diceCount - 1)) {
				rolls += std::to_string(roll) + ", ";
			} else {
				rolls += std::to_string(roll) + " ";
			}
		}

		std::string replyMessage = "You rolled **" + std::to_string(diceCount) + " d" + std::to_string(diceValue) + "**: " + rolls;
		if (diceCount > 1) {
			replyMessage += "Total: **" + std::to_string(total) + "**";
		}

		event.reply(replyMessage);
	}
}