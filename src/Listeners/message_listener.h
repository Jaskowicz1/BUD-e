#pragma once

#include <dpp/dpp.h>

class message_listener {

public:

    /* Create a static function that can be called anywhere. */
    static void on_message_create(const dpp::message_create_t& event);

};
