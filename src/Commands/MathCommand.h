#pragma once

#include "Core/Command.h"
#include "../Utils/EmbedBuilder.h"
#include "../BUDe.h"

class MathCommand : public Command {

public:

    MathCommand() : Command("math", "A quick maths question!") {};

    void Execute(const dpp::slashcommand_t& event) override {

        if(event.command.get_issuing_user().id != 447098177879932939) {
            event.reply("You do not have enough permissions to run this command!");
            return;
        }

        /* Create a message */
        dpp::message msg(event.command.channel_id, "What is 5+5?");

        /* Add an action row, and then 3 buttons within the action row. */
        msg.add_component(
            dpp::component().add_component(
                dpp::component().
                    set_label("9").
                    set_style(dpp::cos_primary).
                    set_id("9")
            ).add_component(
                dpp::component().
                    set_label("10").
                    set_style(dpp::cos_primary).
                    set_id("10")
            ).add_component(
                dpp::component().
                    set_label("11").
                    set_style(dpp::cos_primary).
                    set_id("11")
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