#pragma once

#include "Core/Command.h"
#include "../Utils/EmbedBuilder.h"
#include "../BUDe.h"

class AnnouncementCommand : public Command {

public:

    AnnouncementCommand() : Command("announcement", "Create an announcement for BUD-e's tower.") {};

    void Execute(const dpp::slashcommand_t& event) override {

        if(event.command.get_issuing_user().id != 447098177879932939) {
            event.reply(dpp::message("You do not have enough permissions to run this command!").set_flags(dpp::m_ephemeral));
            return;
        }

        dpp::cache<dpp::message> message_cache;

        dpp::message test("Announcement!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");

        message_cache.store(&test);

        dpp::message* find_msg = message_cache.find(test.id.str());

        event.reply(find_msg->content);

        // Channel ID can be public here, not bothered because only BUD-e has write perms in there.
        BUDe::botRef->message_create(dpp::message(667402621333798923, EmbedBuilder::BasicEmbed(dpp::colours::aqua,
           std::get<std::string>(event.get_parameter("title")),
           std::get<std::string>(event.get_parameter("text")))));

        event.reply(dpp::message("Announcement has been sent.").set_flags(dpp::m_ephemeral));
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