#pragma once

#include "Core/Command.h"

class RPSCommand : public Command {

public:

    RPSCommand() : Command("rps", "Play Rock, Paper, Scissors!") {};

    void Execute(const dpp::slashcommand_t& event) override {
        event.reply(dpp::message(event.command.channel_id, EmbedBuilder::BasicEmbed(dpp::colours::aqua,
        "Rock, Paper Scissors!",
        "Let's play rock, paper, scissors! You pick and I'll pick!")
        ) // End of message()
        .add_component ( // Add component to message
            dpp::component() // comp class
                .add_component(
                dpp::component().set_label("Rock").
                    set_type(dpp::cot_button).
                    set_emoji(u8"🪨").
                    set_style(dpp::cos_primary).
                    set_id("rock")
                )
                .add_component(
                dpp::component().set_label("Paper").
                    set_type(dpp::cot_button).
                    set_emoji(u8"📰").
                    set_style(dpp::cos_primary).
                    set_id("paper")
                )
                .add_component(
                dpp::component().set_label("Scissors").
                    set_type(dpp::cot_button).
                    set_emoji(u8"✂️").
                    set_style(dpp::cos_primary).
                    set_id("scissors")
                )
        ));
    }

    bool Enabled() override {
        return true;
    }

    bool Private() override {
        return true;
    }

};