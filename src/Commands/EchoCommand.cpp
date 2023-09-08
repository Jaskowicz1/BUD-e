#include "EchoCommand.h"
#include "../BUDe.h"

void EchoCommand::Execute(const dpp::slashcommand_t &event) {

    dpp::snowflake channelID = std::get<dpp::snowflake>(event.get_parameter("channel"));
    std::string messagetxt = std::get<std::string>(event.get_parameter("message"));
    dpp::message message(messagetxt);
    message.set_channel_id(channelID);

    BUDe::botRef->message_create(message, [event](const dpp::confirmation_callback_t& callback) {
       if(callback.is_error()) {
           event.reply("Failed to send the message to that channel.");
           return;
       }

       event.reply(dpp::message("Message was sent successfully!").set_flags(dpp::m_ephemeral));
    });
}
