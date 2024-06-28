#pragma once

#include "command.h"

class avatar_command : public command {

public:

	avatar_command() : command("avatar", "Display your avatar as a downloadable image!") {};

	dpp::coroutine<void> execute(dpp::slashcommand_t event) override;

	std::vector<dpp::command_option> command_options() override {
		std::vector<dpp::command_option> temp;
		temp.emplace_back(dpp::co_mentionable, "user", "The user's avatar to retrieve.", false);
		return temp;
	}
};