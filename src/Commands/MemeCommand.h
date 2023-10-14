#pragma once

#include "Core/Command.h"

class MemeCommand : public Command {

public:

	MemeCommand() : Command("meme", "Create a meme, from an image!") {};

	dpp::coroutine<void> Execute(dpp::slashcommand_t event) override;

	std::vector<dpp::command_option> CommandOptions() override {
		std::vector<dpp::command_option> temp;
		temp.emplace_back(dpp::co_string, "toptext", "The top text of the meme.", true);
		temp.emplace_back(dpp::co_string, "bottomtext", "The bottom text of the meme.", true);
		temp.emplace_back(dpp::co_string, "imageurl", "The image url you want to meme.", true);
		return temp;
	}

};
