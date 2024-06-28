#pragma once

#include "command.h"

class echo_command : public command {

public:

	echo_command() : command("echo", "Send a message in a different channel.", dpp::p_administrator) {};

	dpp::coroutine<void> execute(dpp::slashcommand_t event) override;

	std::vector<dpp::command_option> command_options() override {
		std::vector<dpp::command_option> temp;
		temp.emplace_back(dpp::co_channel, "channel", "The channel to send the message to", true);
		temp.emplace_back(dpp::co_string, "message", "message", true);
		return temp;
	}

};
