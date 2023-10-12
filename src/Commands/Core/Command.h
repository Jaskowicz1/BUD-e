#pragma once

#include <string>
#include <utility>
#include <dpp/dpp.h>

class Command {

public:

    Command(std::string_view name, std::string_view description, dpp::permissions permission = dpp::p_use_application_commands) : commandName(name), commandDescription(description), commandPermission(permission) {};

    virtual ~Command() = default;

    virtual dpp::coroutine<void> Execute(dpp::slashcommand_t event) = 0;

    virtual std::vector<dpp::command_option> CommandOptions() {
        // empty vector.
        return {};
    };

    virtual bool Enabled() {
        return true;
    };

    virtual bool Private() {
        return false;
    };
    
    std::string commandName;
    std::string commandDescription;
    dpp::permissions commandPermission;

};