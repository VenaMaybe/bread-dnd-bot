#pragma once

#include <dpp/dpp.h>

namespace ping_command {
	// Global command name
	inline constexpr const char* commandName = "ping";

	// A function to handle the command
	void handlePing(const dpp::slashcommand_t& event);
}