#pragma once

#include "Core/Command.h"

class BallsTugCommand : public Command {

public:

	BallsTugCommand() : Command("ballstug", "Give your balls a tug!") {};

	dpp::coroutine<void> Execute(dpp::slashcommand_t event) override;

};
