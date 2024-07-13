#pragma once

#include "command.h"

class info_command : public command {

public:

	info_command() : command("info", "Show bot information") {};

	dpp::coroutine<void> execute(dpp::slashcommand_t event) override;

};
