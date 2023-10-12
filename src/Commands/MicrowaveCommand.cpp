#include "MicrowaveCommand.h"
#include "../BUDe.h"

dpp::coroutine<void> MicrowaveCommand::Execute(dpp::slashcommand_t event) {

	std::string item = event.get_parameter("item").index() == 0 ? "food" : std::get<std::string>(event.get_parameter("item"));

	if(item == BUDe::botRef->me.get_mention()) {
		co_await event.co_reply(dpp::message("Beep Boop what are you doing step-cyborg?").set_flags(dpp::m_ephemeral));
		co_return;
	}

	co_await event.co_reply("mmmmmmmmmmmmmmmmmmmmmmmmmmm");

	co_await event.from->creator->co_sleep(5);

	co_await event.co_edit_response("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm");

	co_await event.from->creator->co_sleep(5);

	co_await event.co_edit_response("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm");

	co_await event.from->creator->co_sleep(5);

	// Copy item.
	std::string item_lower = item;
	// Make item_lower, all lower case.
	std::transform(item_lower.begin(), item_lower.end(), item_lower.begin(), [](unsigned char c){ return std::tolower(c); });

	std::string message = "Ding! Your " + item + " is ready!";

	std::cout << message << "\n";

	if(item_lower == "iphone" || item_lower == "samsung" || item_lower == "phone") {
		message = "Di- Oh. It appears the phone may have blown up.";
	}

	event.edit_response(message);
}
