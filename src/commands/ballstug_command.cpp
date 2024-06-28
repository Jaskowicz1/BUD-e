#include "commands/ballstug_command.h"
#include "BUDe.h"

dpp::coroutine<void> ballstug_command::execute(dpp::slashcommand_t event) {
	dpp::http_request_completion_t request = co_await BUDe::botRef->co_request("https://jaskowicz.xyz/giveyaballsatug.jpg", dpp::m_get);

	dpp::message msg{""};
	if (request.status == 200) {
		msg.add_file("tug.png", request.body);
	} else {
		event.reply(dpp::message{"Failed to get the image!"}.set_flags(dpp::m_ephemeral));
		co_return;
	}

	co_return event.reply(msg);
}
