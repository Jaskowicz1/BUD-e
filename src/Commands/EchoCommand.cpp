#include "EchoCommand.h"
#include "../BUDe.h"

dpp::coroutine<void> EchoCommand::Execute(dpp::slashcommand_t event) {

    dpp::snowflake channelID = std::get<dpp::snowflake>(event.get_parameter("channel"));
    std::string messagetxt = std::get<std::string>(event.get_parameter("message"));
    dpp::message message(messagetxt);
    message.set_channel_id(channelID);

    dpp::confirmation_callback_t confirmation = co_await BUDe::botRef->co_message_create(message);

    if(confirmation.is_error()) {
	event.reply(dpp::message("The message failed to send!").set_flags(dpp::m_ephemeral));
    } else {
	event.reply(dpp::message("The message was sent successfully!").set_flags(dpp::m_ephemeral));
    }
}
