#pragma once

#include "Core/Command.h"

class PingCommand : public Command {

public:

    PingCommand() : Command("ping", "Ping Pong!") {};

    void Execute(const dpp::slashcommand_t& event) override {
        event.reply("Pong! The rest ping is: " + std::to_string(BUDe::botRef->rest_ping));
    }

    bool Enabled() override {
        return true;
    }

};