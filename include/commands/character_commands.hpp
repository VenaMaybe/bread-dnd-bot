#pragma once

#include <dpp/dpp.h>

namespace create_character_command {
	// Global command name
	inline constexpr const char* commandName = "create_character";

	// Handles registration of the command and its options
	void register_command(dpp::cluster& bot);

	// Handles invocation of command
	void handle_command(const dpp::slashcommand_t& event);
}

namespace view_character_command {
	// Global command name
	inline constexpr const char* commandName = "view_character";

	// Handles registration of the command and its options
	void register_command(dpp::cluster& bot);

	// Handles invocation of command
	void handle_command(const dpp::slashcommand_t& event);
}

namespace edit_character_command {
	// Global command name
	inline constexpr const char* commandName = "edit_character";

	// Handles registration of the command and its options
	void register_command(dpp::cluster& bot);

	// Handles invocation of command
	void handle_command(const dpp::slashcommand_t& event);
}