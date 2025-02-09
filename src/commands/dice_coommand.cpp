#include "commands/dice_command.h"
#include <random>

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