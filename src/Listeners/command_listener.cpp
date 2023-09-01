#include "command_listener.h"
#include "../BUDe.h"


void command_listener::on_slashcommand(const dpp::slashcommand_t &event) {
    for(auto& cmd : BUDe::commands) {
        if(cmd->commandName == event.command.get_command_name()) {
            // The command was right

            // If the command is disabled, we just want to reply to the user so the interaction doesn't fail,
            // then we just want to stop.
            if(!cmd->Enabled()) {
                event.reply(dpp::message("This command is disabled!").set_flags(dpp::m_ephemeral));
                return;
            }

            // If the command is private and the user executing the command isn't me then tell the user and stop.
            if(cmd->Private() && event.command.usr.id.str() != "447098177879932939") {
                event.reply(dpp::message("You do not have enough permissions to run this command!").set_flags(dpp::m_ephemeral));
                return;
            }

            cmd->Execute(event);
            return;
        }
    }
}
