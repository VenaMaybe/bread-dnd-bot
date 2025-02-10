#include "commands/ping_command.hpp"

namespace ping_command {
	void handlePing(const dpp::slashcommand_t& event) {
		event.reply("Pong :3");
	}
}