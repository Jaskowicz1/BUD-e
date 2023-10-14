#pragma once

#include "Core/Command.h"
#include "../Utils/EmbedBuilder.h"
#include "../BUDe.h"

class AnnouncementCommand : public Command {

public:

	AnnouncementCommand() : Command("announcement", "Create an announcement for BUD-e's tower.") {};

	dpp::coroutine<void> Execute(dpp::slashcommand_t event) override {
		// Channel ID can be public here, not bothered because only BUD-e has write perms in there.

		dpp::confirmation_callback_t confirmation = co_await BUDe::botRef->co_message_create(
			dpp::message(667402621333798923,
				EmbedBuilder::BasicEmbed(
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
	};

	std::vector<dpp::command_option> CommandOptions() override {
		std::vector<dpp::command_option> temp;
		temp.emplace_back(dpp::co_string, "title", "The title of the announcement", true);
		temp.emplace_back(dpp::co_string, "text", "The announcement text", true);
		return temp;
	}

	bool Enabled() override {
		return true;
	}

	bool Private() override {
		return true;
	}

};