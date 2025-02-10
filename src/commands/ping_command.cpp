#include "commands/ping_command.hpp"

namespace ping_command {
	void register_command(dpp::cluster& bot) {
		bot.global_command_create(
			dpp::slashcommand("ping", "Ping command", bot.me.id)
		);
	}

	void handlePing(const dpp::slashcommand_t& event) {
		event.reply("Pong :3 v1.2");
	}
}