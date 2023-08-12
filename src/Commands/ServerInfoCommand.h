#pragma once

#include "Core/Command.h"
#include "../Utils/EmbedBuilder.h"

class ServerInfoCommand : public Command {

public:

    ServerInfoCommand() : Command("serverinfo", "Display information about the server.") {};

    void Execute(const dpp::slashcommand_t& event) override {

        if(!event.command.get_guild().base_permissions(&event.command.get_issuing_user()).has(dpp::permissions::p_administrator)) {
            event.reply("You don't have access to run this.");
            return;
        }

        dpp::embed embed(EmbedBuilder::BasicEmbed(dpp::colours::aqua,"Showing information for: '" + event.command.get_guild().name + "':",
                                                  "This information is based on your server. If anything seems incorrect, contact the team (you can find me with /credits)!"));

        dpp::embed_field membersField;
        membersField.name = "Member count:";
        membersField.value = event.command.get_guild().member_count;
        membersField.is_inline = true;

        dpp::embed_field dateField;
        dateField.name = "Date created:";
        dateField.value = event.command.get_guild().get_creation_time();
        dateField.is_inline = true;

        dpp::embed_field ownerField;
        ownerField.name = "Owner (id):";
        ownerField.value = event.command.get_guild().owner_id;
        ownerField.is_inline = true;

        EmbedBuilder::AddFieldToEmbed(embed, membersField);
        EmbedBuilder::AddFieldToEmbed(embed, dateField);
        EmbedBuilder::AddFieldToEmbed(embed, ownerField);

        embed.set_footer("Data provided by Discord.", "");
        embed.set_thumbnail(event.command.get_guild().get_icon_url());

        dpp::message msg(event.command.channel_id, embed);

        event.reply(msg);
    }

    bool Enabled() override {
        return true;
    }

};