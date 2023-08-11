#pragma once

#include "Core/Command.h"
#include "../Utils/EmbedBuilder.h"

class UserInfoCommand : public Command {

public:

    UserInfoCommand() : Command("userinfo", "Display information about yourself!") {};

    void Execute(const dpp::slashcommand_t& event) override {

        dpp::message msg("");

        dpp::embed embed(EmbedBuilder::BasicEmbed(dpp::colours::aqua,"Showing information for: '" + event.command.get_issuing_user().username + "':",
                                 "This information is based on your account. If anything seems incorrect, contact the team (you can find me with /credits)!"));

        dpp::embed_field nitroField;
        nitroField.name = "Has Nitro:";
        nitroField.value = event.command.get_issuing_user().has_nitro_basic() || event.command.get_issuing_user().has_nitro_classic() || event.command.get_issuing_user().has_nitro_full();
        nitroField.is_inline = true;

        dpp::embed_field dateField;
        dateField.name = "Date created:";
        dateField.value = event.command.get_issuing_user().get_creation_time();
        dateField.is_inline = true;

        dpp::embed_field idField;
        idField.name = "User ID:";
        idField.value = event.command.get_issuing_user().id;
        idField.is_inline = true;

        EmbedBuilder::AddFieldToEmbed(embed, nitroField);
        EmbedBuilder::AddFieldToEmbed(embed, dateField);
        EmbedBuilder::AddFieldToEmbed(embed, idField);

        embed.set_footer("Data provided by Discord.", "");
        embed.set_thumbnail(event.command.get_guild().get_icon_url());

        msg.set_flags(dpp::m_ephemeral);

        event.reply(msg);
    }

    bool Enabled() override {
        return true;
    }

    bool Private() override {
        return true;
    }

};