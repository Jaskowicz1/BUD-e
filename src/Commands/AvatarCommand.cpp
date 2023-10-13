#include "AvatarCommand.h"
#include "../BUDe.h"

dpp::coroutine<void> AvatarCommand::Execute(dpp::slashcommand_t event) {

    /* If there was no specified user, we set the "user" variable to the command author (issuing user). */
    dpp::snowflake user_id = event.get_parameter("user").index() == 0 ? event.command.get_issuing_user().id : std::get<dpp::snowflake>(event.get_parameter("user"));

    dpp::user* user = dpp::find_user(user_id);

    if(!user) {
        event.reply("I failed to find that user. Please try again later. If the issue persists, please get in contact!");
        co_return;
    }

    dpp::embed embed = EmbedBuilder::BasicEmbed(dpp::colours::aqua,user->username + "'s Avatar!",
						"Here's " + user->username + "'s avatar! You can right click the image to save it.");

    embed.set_image(user->get_avatar_url(256));

    dpp::message msg(event.command.channel_id, embed);

    msg.set_flags(dpp::m_ephemeral);

    event.reply(msg);
}
