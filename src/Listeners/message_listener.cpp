#include "message_listener.h"

void message_listener::on_message_create(const dpp::message_create_t &event) {
    /* See if the message contains the phrase we want to check for.
     * If there's at least a single match, we reply and say it's not allowed.
     */
    if (event.msg.content.find("bad word") != std::string::npos) {
        event.reply("That is not allowed here. Please, mind your language!", true);
    }
}
