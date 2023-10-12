#pragma once

#include "Core/Command.h"

class MicrowaveCommand : public Command {

public:

    MicrowaveCommand() : Command{"microwave", "mmmmmmmmmmmmm."} {};

    dpp::coroutine<void> Execute(dpp::slashcommand_t event) override;

    std::vector<dpp::command_option> CommandOptions() override {
	    std::vector<dpp::command_option> temp;
	    temp.emplace_back(dpp::co_string, "item", "An item to microwave.", false);
	    return temp;
    }
};
