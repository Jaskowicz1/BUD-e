#pragma once

#include "Core/Command.h"

class CreateThreadCommand : public Command {

public:

    CreateThreadCommand() : Command("create-thread", "Create a thread!") {};

    void Execute(const dpp::slashcommand_t& event) override;

    bool Enabled() override {
	return true;
    }

    bool Private() override {
	return true;
    }

};
