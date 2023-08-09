#pragma once

#include "Core/Command.h"
#include "../Utils/EmbedBuilder.h"

class UserInfoCommand : public Command {

public:

    UserInfoCommand() : Command("userinfo", "Display information about a specific user.") {};

    void Execute(const dpp::slashcommand_t& event) override {

        dpp::message msg("");

        dpp::embed embed(EmbedBuilder::BasicEmbed(dpp::colours::aqua,"Showing information for: '" + event.command.get_guild().name + "':",
                                 "This information is based on your server. If anything seems incorrect, contact the team (you can find me with /credits)!"));

        dpp::embed_field membersField;
        membersField.name = "Member count:";
        membersField.value = event.command.get_guild().member_count;
        membersField.is_inline = true;

        dpp::embed_field dateField;
        membersField.name = "Date created:";
        membersField.value = event.command.get_guild().get_creation_time();
        membersField.is_inline = true;

        dpp::embed_field ownerField;
        membersField.name = "Owner (id):";
        membersField.value = event.command.get_guild().owner_id;
        membersField.is_inline = true;

        EmbedBuilder::AddFieldToEmbed(embed, {membersField, dateField, ownerField});

        embed.set_footer("Data provided by Discord.", "");
        embed.set_thumbnail(event.command.get_guild().get_icon_url());

        msg.set_flags(dpp::m_ephemeral);

        event.reply(msg);
    }

    bool Enabled() override {
        return false;
    }

    bool Private() override {
        return true;
    }

};