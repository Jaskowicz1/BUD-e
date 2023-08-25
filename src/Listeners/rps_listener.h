#pragma once

#include <dpp/dpp.h>
#include <random>
#include "../Utils/EmbedBuilder.h"
#include "../Utils/ComponentBuilder.h"

class rps_listener {

public:

    static void on_button_click(const dpp::button_click_t& event);

};