#pragma once

#include "Core/Command.h"
#include "../EmbedBuilder.h"

class CreditsCommand : public Command {

public:

    CreditsCommand() : Command("credits", "Credits of BUD-e.") {};

    void Execute(const dpp::slashcommand_t& event) override {
        std::string str;

        str = std::string("Thank you for using BUD-e! I greatly appreciate it and, from the bottom of my heart, I love you.\n") +
              std::string("\n") +
              std::string("Creator & Developer - Archie Jaskowicz (@JaskowiczArchie, jaskowicz)\n") +
              std::string("BUD-e's Discord - https://bude.rocketeersgaming.net\n") +
              std::string("Rocketeers Discord - https://discord.rocketeersgaming.net\n") +
              std::string("Add BUD-e to another server - https://basicutilitydroid.io\n") +
              std::string("\n") +
              std::string("APIs used:\n") +
              std::string("- D++\n") +
              std::string("\n") +
              std::string("Again, Thank you for all the support. I love you all and I'm so happy to see you using BUD-e once again.");

        event.reply(dpp::message(event.command.channel_id, EmbedBuilder::BasicEmbed(dpp::colours::aqua,
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