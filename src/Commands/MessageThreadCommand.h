#pragma once

#include "Core/Command.h"

class MessageThreadCommand : public Command {

public:

    MessageThreadCommand() : Command("message-thread", "Message a thread!") {};

    void Execute(const dpp::slashcommand_t& event) override;

    bool Enabled() override {
	return true;
    }

    bool Private() override {
	return true;
    }

};
