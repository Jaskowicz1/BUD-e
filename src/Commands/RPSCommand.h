#pragma once

#include "Core/Command.h"
#include "../Utils/ComponentBuilder.h"
#include <dpp/unicode_emoji.h>

class RPSCommand : public Command {

public:

	RPSCommand() : Command("rps", "Play Rock, Paper, Scissors!") {};

	dpp::coroutine<void> Execute(dpp::slashcommand_t event) override {
		dpp::message msg(event.command.channel_id,
			EmbedBuilder::BasicEmbed(dpp::colours::aqua,"Rock, Paper Scissors!",
			"Let's play rock, paper, scissors! You pick and I'll pick!")
		);

		ComponentBuilder::AddButtonsToMessage(msg, {
			ComponentData{"Rock", "rock", dpp::unicode_emoji::rock},
			ComponentData{"Paper", "paper", dpp::unicode_emoji::newspaper},
			ComponentData{"Scissors", "scissors", dpp::unicode_emoji::scissors}
		});

		co_return event.reply(msg);
	}

	bool Enabled() override {
	return true;
	}

};