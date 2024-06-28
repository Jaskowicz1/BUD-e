#include "commands/command.h"

std::vector<dpp::command_option> command::command_options() {
    // Empty vector on purpose.
    return {};
}

bool command::is_enabled() {
    return true;
}

bool command::is_private() {
    return false;
}

