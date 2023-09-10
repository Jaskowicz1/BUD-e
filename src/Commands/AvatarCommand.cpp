#include "AvatarCommand.h"
#include "../BUDe.h"

void AvatarCommand::Execute(const dpp::slashcommand_t &event) {

    /* If there was no specified user, we set the "user" variable to the command author (issuing user). */
    dpp::snowflake user = event.get_parameter("user").index() == 0 ? event.command.get_issuing_user().id : std::get<dpp::snowflake>(event.get_parameter("user"));

    BUDe::botRef->user_get_cached(user, [event](const dpp::confirmation_callback_t& callback) {
	if(callback.is_error()) {
	    event.reply("I failed to find that user. Please try again later. If the issue persists, please get in contact!");
	    return;
	}

	auto usr = callback.get<dpp::user_identified>();

	dpp::embed embed = EmbedBuilder::BasicEmbed(dpp::colours::aqua,usr.username + "'s Avatar!",
						    "Here's " + usr.username + "'s avatar! You can right click the image to save it.");

	embed.set_image(usr.get_avatar_url(256));

	dpp::message msg(event.command.channel_id, embed);

	msg.set_flags(dpp::m_ephemeral);

	event.reply(msg);
    });
}
