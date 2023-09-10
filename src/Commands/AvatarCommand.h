#pragma once

#include "Core/Command.h"
#include "../Utils/ComponentBuilder.h"
#include "../Utils/EmbedBuilder.h"

class AvatarCommand : public Command {

public:

    AvatarCommand() : Command("avatar", "Display your avatar as a downloadable image!") {};

    void Execute(const dpp::slashcommand_t& event) override;

    std::vector<dpp::command_option> CommandOptions() override {
	std::vector<dpp::command_option> temp;
	temp.emplace_back(dpp::co_mentionable, "user", "The user's avatar to retrieve.", false);
	return temp;
    }

    bool Enabled() override {
        return true;
    }

};