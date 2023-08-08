#pragma once

#include "Core/Command.h"

class PongCommand : public Command {

public:

    PongCommand() : Command("pong", "Pong Ping!") {};

    void Execute(const dpp::slashcommand_t& event) override {
        event.reply("Ping!");
    }

    bool Enabled() override {
        return true;
    }

};