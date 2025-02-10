#pragma once

#include <dpp/dpp.h>

namespace dice_command {
	// Global command name
	inline constexpr const char* commandName = "roll";

	// Handles registration of the dice command and its options
	void register_command(dpp::cluster& bot);

	// Handles invocation of dice command
	void handleDice(const dpp::slashcommand_t& event);
}
