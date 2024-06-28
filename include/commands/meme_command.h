#pragma once

#include "command.h"

class meme_command : public command {

public:

	meme_command() : command("meme", "Create a meme, from an image!") {};

	dpp::coroutine<void> execute(dpp::slashcommand_t event) override;

	std::vector<dpp::command_option> command_options() override {
		std::vector<dpp::command_option> temp;
		temp.emplace_back(dpp::co_string, "toptext", "The top text of the meme.", true);
		temp.emplace_back(dpp::co_string, "bottomtext", "The bottom text of the meme.", true);
		temp.emplace_back(dpp::co_string, "imageurl", "The image url you want to meme.", true);
		return temp;
	}

};
