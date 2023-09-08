#pragma once

#include "Core/Command.h"
#include "../Utils/EmbedBuilder.h"
#include "../BUDe.h"

class EmbedCommand : public Command {

public:

    EmbedCommand() : Command("embed", "Send a test embed!") {};

    void Execute(const dpp::slashcommand_t& event) override;

    bool Enabled() override {
        return true;
    }

    bool Private() override {
        return true;
    }

};