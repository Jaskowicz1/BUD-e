#pragma once

#include "command.h"
#include "BUDe.h"

class announcement_command : public command {

public:

	announcement_command() : command("announcement", "Create an announcement for BUD-e's tower.") {};

	dpp::coroutine<void> execute(dpp::slashcommand_t event) override;

	std::vector<dpp::command_option> command_options() override;

	bool is_enabled() override {
		return true;
	}

	bool is_private() override {
		return true;
	}

};