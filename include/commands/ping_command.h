#pragma once

#include "command.h"

class ping_command : public command {

public:

	ping_command() : command("ping", "Ping Pong!") {};

	dpp::coroutine<void> execute(dpp::slashcommand_t event) override {
		co_return event.reply("Pong! The rest ping is: " + std::to_string(BUDe::botRef->rest_ping * 1000) + "ms");
	}

};