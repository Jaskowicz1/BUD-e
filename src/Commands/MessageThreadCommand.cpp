#include "MessageThreadCommand.h"
#include "../BUDe.h"

void MessageThreadCommand::Execute(const dpp::slashcommand_t &event) {

    /* Get all active threads in a guild. */
    BUDe::botRef->threads_get_active(event.command.guild_id, [event](const dpp::confirmation_callback_t& callback) {

	if(callback.is_error()) {
	    event.reply("Failed to get threads!");
	    return;
	}

	/* Get the list of active threads in the guild. */
	auto threads = callback.get<dpp::active_threads>();

	dpp::snowflake thread_id;

	/* Loop through the threads, getting each value in the map. Then we get the first value and then break off.
	 * The reason we're getting only the first value is because, for this example, we'll just assume you've only got a single active thread (the one created by the bot)
	 */
	for(const auto& _thread : threads) {
	    thread_id = _thread.first;
	    break;
	}

	/* Send a message in the first thread we find. */
	BUDe::botRef->message_create(dpp::message(thread_id, "Hey, I'm first to message in a cool thread!"), [event](const dpp::confirmation_callback_t& callback2) {
	    if(callback2.is_error()) {
		    event.reply("Failed to send a message in a thread.");
		    return;
	    }

	    event.reply("I've sent a message in the specified thread.");
	});
    });

}
