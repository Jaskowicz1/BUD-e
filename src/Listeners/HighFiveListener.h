#pragma once

#include <dpp/dpp.h>
#include <random>
#include "../Utils/EmbedBuilder.h"
#include "../Utils/ComponentBuilder.h"

class HighFiveListener {

public:

    static void OnUserContextMenu(const dpp::user_context_menu_t &event) {

        /* check if the context menu name is High Five */
        if (event.command.get_command_name() == "high five") {
            dpp::user user = event.get_user(); // the user who the command has been issued on
            dpp::user author = event.command.get_issuing_user(); // the user who clicked on the context menu
            event.reply(author.get_mention() + " slapped " + user.get_mention());
        }
    }

};