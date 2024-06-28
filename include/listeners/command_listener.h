#pragma region

#include "dpp/dpp.h"

class command_listener {

public:

	static dpp::task<void> on_slashcommand(dpp::slashcommand_t event);
};
