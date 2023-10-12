#pragma once

#include "Core/Command.h"
#include "../Utils/EmbedBuilder.h"

class CreditsCommand : public Command {

public:

    CreditsCommand() : Command("credits", "Credits of BUD-e.") {};

    dpp::coroutine<void> Execute(dpp::slashcommand_t event) override {
        std::string str;

        str = std::string("Thank you for using BUD-e! I greatly appreciate it!\n") +
              std::string("\n") +
              std::string("Creator & Developer - Archie Jaskowicz (@JaskowiczArchie, jaskowicz)\n") +
              std::string("BUD-e's Discord - https://bude.rocketeersgaming.net\n") +
              std::string("Rocketeers Discord - https://discord.rocketeersgaming.net\n") +
              std::string("Add BUD-e to another server - https://basicutilitydroid.io\n") +
              std::string("\n") +
              std::string("APIs used:\n") +
              std::string("- D++\n") +
              std::string("\n") +
              std::string("Extra thanks to the people over at the D++ discord for helping me get everything working!") +
              std::string("\n") +
              std::string("Again, Thank you for all the support and thank you for using BUD-e!");

	co_return event.reply(dpp::message(event.command.channel_id, EmbedBuilder::BasicEmbed(dpp::colours::aqua,
            "BUD-e - Credits.",
            str)).set_flags(dpp::m_ephemeral));
    };

    bool Enabled() override {
        return true;
    }

    bool Private() override {
        return false;
    };

};