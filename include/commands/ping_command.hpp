#pragma once

#include <dpp/dpp.h>

namespace ping_command {
	// Global command name
	inline constexpr const char* commandName = "ping";

	// Handles registration of the dice command and its options
	void register_command(dpp::cluster& bot);

	// A function to handle the command
	void handlePing(const dpp::slashcommand_t& event);
}