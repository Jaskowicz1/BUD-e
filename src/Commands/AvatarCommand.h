#pragma once

#include "Core/Command.h"
#include "../Utils/ComponentBuilder.h"
#include "../Utils/EmbedBuilder.h"

class AvatarCommand : public Command {

public:

    AvatarCommand() : Command("avatar", "Display your avatar as a downloadable image!") {};

    void Execute(const dpp::slashcommand_t& event) override {

        dpp::embed embed = EmbedBuilder::BasicEmbed(dpp::colours::aqua,event.command.get_issuing_user().username + "'s Avatar!",
                                                   "Here's your avatar! You can right click the image to save it.");

        embed.set_image(event.command.get_issuing_user().avatar.to_string());

        dpp::message msg(event.command.channel_id, embed);

        msg.set_flags(dpp::m_ephemeral);

        event.reply(msg);
    }

    bool Enabled() override {
        return true;
    }

    bool Private() override {
        return false;
    }

};