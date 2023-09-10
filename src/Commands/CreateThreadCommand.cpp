#include "CreateThreadCommand.h"
#include "../BUDe.h"

void CreateThreadCommand::Execute(const dpp::slashcommand_t &event) {

    /* Here we create a thread in the current channel. It will expire after 60 minutes of inactivity. We'll also allow other mods to join, and we won't add a slowdown timer. */
    BUDe::botRef->thread_create("Cool thread!", event.command.channel_id, 60, dpp::channel_type::CHANNEL_PUBLIC_THREAD, true, 0, [event](const dpp::confirmation_callback_t& callback) {
	if(callback.is_error()) {
	    event.reply("Failed to create a thread!");
	    return;
	}

	event.reply("Created a thread for you!");
    });
}
