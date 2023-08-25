#pragma region

#include <dpp/dpp.h>

class command_listener {

public:

    static void on_slashcommand(const dpp::slashcommand_t& event);

};
