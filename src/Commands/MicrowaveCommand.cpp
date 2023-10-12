#include "MicrowaveCommand.h"

dpp::coroutine<void> MicrowaveCommand::Execute(dpp::slashcommand_t event) {
	co_await event.co_reply("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm");

	co_await event.from->creator->co_sleep(5);

	co_await event.co_edit_response("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm");

	co_await event.from->creator->co_sleep(5);

	co_await event.co_edit_response("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm");

	co_await event.from->creator->co_sleep(5);

	event.edit_response("Ding! Your pizza is ready!");
}
