#pragma once

#include "EmbedBuilder.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <dpp/dpp.h>

namespace BUDe
{
	std::string token = "";

	dpp::cluster* botRef;

	void callback_handler(int signum);

	void ChangeStatus();
};
