#pragma once

#include "Core/Command.h"
#include "../Utils/ComponentBuilder.h"

class RPSCommand : public Command {

public:

    RPSCommand() : Command("rps", "Play Rock, Paper, Scissors!") {};

    void Execute(const dpp::slashcommand_t& event) override {

        dpp::message msg(event.command.channel_id,
                         EmbedBuilder::BasicEmbed(dpp::colours::aqua,"Rock, Paper Scissors!",
                        "Let's play rock, paper, scissors! You pick and I'll pick!")
        );

        ComponentBuilder::AddButtonsToMessage(msg, {ComponentData("Rock", "rock", u8"🪨"),
                                                   ComponentData("Paper", "paper", u8"📰"),
                                                   ComponentData("Scissors", "scissors", u8"✂️")});

        event.reply(msg);
    }

    bool Enabled() override {
        return true;
    }

    bool Private() override {
        return false;
    }

};