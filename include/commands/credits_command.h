#pragma once

#include "command.h"

class credits_command : public command {

public:

    credits_command() : command("credits", "Credits of BUD-e.") {};

    dpp::coroutine<void> execute(dpp::slashcommand_t event) override;

    bool is_enabled() override {
        return true;
    }

    bool is_private() override {
        return false;
    };

};