#pragma once

#include "Core/Command.h"
#include "../BUDe.h"

class PMCommand : public Command {

public:

    PMCommand() : Command("pm", "Send a private message.") {};

    void Execute(const dpp::slashcommand_t& event) override;

    std::vector<dpp::command_option> CommandOptions() override {
        std::vector<dpp::command_option> temp;
        temp.emplace_back(dpp::co_mentionable, "user", "The user to message.", false);
        return temp;
    }

    bool Enabled() override {
        return true;
    }

    bool Private() override {
        return true;
    }

};