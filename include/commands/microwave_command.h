#pragma once

#include "command.h"

class microwave_command : public command {

public:

    microwave_command() : command{"microwave", "mmmmmmmmmmmmm."} {};

    dpp::coroutine<void> execute(dpp::slashcommand_t event) override;

    std::vector<dpp::command_option> command_options() override {
	    std::vector<dpp::command_option> temp;
	    temp.emplace_back(dpp::co_string, "item", "An item to microwave.", false);
	    return temp;
    }
};
