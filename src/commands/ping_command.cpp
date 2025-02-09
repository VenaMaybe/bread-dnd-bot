#include "commands/ping_command.h"

void handlePing(const dpp::slashcommand_t& event) {
	event.reply("Pong :3");
}