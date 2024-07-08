#pragma once

#include "dpp/dpp.h"

class rps_listener {

public:

	static dpp::task<void> on_button_click(dpp::button_click_t event);
};