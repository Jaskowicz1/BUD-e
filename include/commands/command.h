#pragma once

#include <string>
#include <utility>
#include <dpp/dpp.h>

class command {

public:

    command(std::string_view name, std::string_view description, dpp::permissions permission = dpp::p_use_application_commands) : command_name(name), command_description(description), command_permission(permission) {};

    virtual ~command() = default;

    virtual dpp::coroutine<void> execute(dpp::slashcommand_t event) = 0;

    virtual std::vector<dpp::command_option> command_options();

    virtual bool is_enabled();

    virtual bool is_private();
    
    std::string command_name{};
    std::string command_description{};
    dpp::permissions command_permission{};

};