#pragma once

#include "Core/Command.h"

class EchoCommand : public Command {

public:

	EchoCommand() : Command("echo", "Send a message in a different channel.", dpp::p_administrator) {};

	dpp::coroutine<void> Execute(dpp::slashcommand_t event) override;

	std::vector<dpp::command_option> CommandOptions() override {
		std::vector<dpp::command_option> temp;
		temp.emplace_back(dpp::co_channel, "channel", "The channel to send the message to", true);
		temp.emplace_back(dpp::co_string, "message", "message", true);
		return temp;
	}

};
