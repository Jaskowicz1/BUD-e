#pragma once

#include "command.h"
#include "utils/embed_builder.h"
#include "utils/component_builder.h"
#include <dpp/unicode_emoji.h>

class rps_command : public command {

public:

	rps_command() : command("rps", "Play Rock, Paper, Scissors!") {};

	dpp::coroutine<void> execute(dpp::slashcommand_t event) override {
		dpp::message msg(event.command.channel_id,
				 embed_builder::basic_embed(dpp::colours::aqua, "Rock, Paper Scissors!",
							   "Let's play rock, paper, scissors! You pick and I'll pick!")
		);

		component_builder::add_buttons_to_message(msg, {
			component_data{"Rock", "rock", dpp::unicode_emoji::rock },
			component_data{"Paper", "paper", dpp::unicode_emoji::newspaper },
			component_data{"Scissors", "scissors", dpp::unicode_emoji::scissors }
		});

		co_return event.reply(msg);
	}

	bool is_enabled() override {
		return true;
	}

};