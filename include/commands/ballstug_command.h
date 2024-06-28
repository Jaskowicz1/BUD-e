#pragma once

#include "command.h"

class ballstug_command : public command {

public:

	ballstug_command() : command("ballstug", "Give your balls a tug!") {};

	dpp::coroutine<void> execute(dpp::slashcommand_t event) override;

};
