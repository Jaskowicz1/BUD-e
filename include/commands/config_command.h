#pragma once

#include "command.h"

class config_command : public command {

public:

	config_command(dpp::cluster& bot);

	dpp::coroutine<void> execute(dpp::slashcommand_t event) override;

	std::vector<dpp::command_option> command_options() override;

	bool is_enabled() override {
		return true;
	}

	bool is_private() override {
		return true;
	}

};