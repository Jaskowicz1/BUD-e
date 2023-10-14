#include "command_listener.h"
#include "../BUDe.h"

dpp::job command_listener::on_slashcommand(dpp::slashcommand_t event) {
	for(auto& cmd : BUDe::commands) {
		if(cmd->commandName == event.command.get_command_name()) {
			// The command was right

			/* If the command is disabled, we just want to reply to the user so the interaction doesn't fail,
			 * then we just want to stop.
			 */
			if(!cmd->Enabled()) {
				co_return event.reply(dpp::message{"This command is disabled!"}.set_flags(dpp::m_ephemeral));
			}

			// If the command is private and the user executing the command isn't me then tell the user and stop.
			if(cmd->Private() && event.command.usr.id.str() != "447098177879932939") {
				co_return event.reply(dpp::message{"You do not have enough permissions to run this command!"}.set_flags(dpp::m_ephemeral));
			}

			/* We wait for the command to finish, otherwise event will invalidate and commands
			 * will not be able to do anything with the data inside event.
			 */
			co_return co_await cmd->Execute(event);
		}
	}
}
