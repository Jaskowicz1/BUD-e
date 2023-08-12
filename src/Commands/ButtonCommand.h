#pragma once

#include "Core/Command.h"
#include "../Utils/EmbedBuilder.h"
#include "../BUDe.h"

class ButtonCommand : public Command {

public:

    ButtonCommand() : Command("button", "Send a message with a button!") {};

    void Execute(const dpp::slashcommand_t& event) override {

        if(event.command.get_issuing_user().id != 447098177879932939) {
            event.reply("You do not have enough permissions to run this command!");
            return;
        }

        dpp::message msg(event.command.channel_id, "this text has buttons");

        /* Add an action row, and then a button within the action row. */
        msg.add_component(
            dpp::component().add_component(
                dpp::component().
                    set_label("Click me!").
                    set_type(dpp::cot_button).
                    set_emoji(u8"😄").
                    set_style(dpp::cos_danger).
                    set_id("myid")
            )
        );

        /* Reply to the user with our message. */
        event.reply(msg);
    };

    bool Enabled() override {
        return true;
    }

    bool Private() override {
        return true;
    }

};