#pragma once

#include "Core/Command.h"

class PingCommand : public Command {

public:

	PingCommand() : Command("ping", "Ping Pong!") {};

	dpp::coroutine<void> Execute(dpp::slashcommand_t event) override {
		co_return event.reply("Pong! The rest ping is: " + std::to_string(BUDe::botRef->rest_ping * 1000) + "ms");
	}

};