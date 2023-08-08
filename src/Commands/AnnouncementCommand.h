#pragma once

#include "Core/Command.h"
#include "../EmbedBuilder.h"
#include "../BUDe.h"

class AnnouncementCommand : public Command {

public:

    AnnouncementCommand() : Command("Announcement", "Create an announcement for BUD-e's tower.") {};

    void Execute(const dpp::slashcommand_t& event) override {
        BUDe::botRef->message_create(dpp::message(667402621333798923, EmbedBuilder::BasicEmbed(dpp::colours::aqua,
           std::get<std::string>(event.get_parameter("title")),
           std::get<std::string>(event.get_parameter("text")))));

        event.reply("AnnouncementCommand has been sent.");
    };

    std::vector<dpp::command_option> CommandOptions() override {
        std::vector<dpp::command_option> temp;
        temp.emplace_back(dpp::co_string, "title", "The title of the announcement", true);
        temp.emplace_back(dpp::co_string, "text", "The announcement text", true);
        return temp;
    }

    bool Enabled() override {
        return true;
    }

    bool Private() override {
        return true;
    }

};