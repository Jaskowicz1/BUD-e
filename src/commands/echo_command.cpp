#include "commands/echo_command.h"
#include "BUDe.h"

dpp::coroutine<void> echo_command::execute(dpp::slashcommand_t event) {
	dpp::message message{
		std::get<dpp::snowflake>(event.get_parameter("channel")),
		std::get<std::string>(event.get_parameter("message"))
	};

	dpp::confirmation_callback_t confirmation = co_await BUDe::botRef->co_message_create(message);

	if(confirmation.is_error()) {
		co_return event.reply(dpp::message("The message failed to send!").set_flags(dpp::m_ephemeral));
	} else {
		co_return event.reply(dpp::message("The message was sent successfully!").set_flags(dpp::m_ephemeral));
	}
}
