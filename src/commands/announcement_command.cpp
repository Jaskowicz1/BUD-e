#include "commands/announcement_command.h"
#include "utils/embed_builder.h"

dpp::coroutine<void> announcement_command::execute(dpp::slashcommand_t event) {
	// Channel ID can be public here, not bothered because only BUD-e has write perms in there.
	dpp::confirmation_callback_t confirmation = co_await BUDe::botRef->co_message_create(
		dpp::message(667402621333798923,
			     embed_builder::basic_embed(
				     dpp::colours::aqua,
				     std::get<std::string>(event.get_parameter("title")),
				     std::get<std::string>(event.get_parameter("text"))
			     )
		)
	);

	if(confirmation.is_error()) {
		co_return event.reply(dpp::message("The announcement failed to send!").set_flags(dpp::m_ephemeral));
	} else {
		co_return event.reply(dpp::message("Announcement has been sent.").set_flags(dpp::m_ephemeral));
	}
}

std::vector<dpp::command_option> announcement_command::command_options() {
	std::vector<dpp::command_option> temp;
	temp.emplace_back(dpp::co_string, "title", "The title of the announcement", true);
	temp.emplace_back(dpp::co_string, "text", "The announcement text", true);
	return temp;
}
