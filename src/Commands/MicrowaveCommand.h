#pragma once

#include "Core/Command.h"

class MicrowaveCommand : public Command {

public:

    MicrowaveCommand() : Command{"microwave", "mmmmmmmmmmmmm."} {};

    dpp::coroutine<void> Execute(dpp::slashcommand_t event) override;
};
