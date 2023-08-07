#pragma once

#include "EmbedBuilder.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <dpp/dpp.h>

namespace BUDe
{

#pragma region Functions

	void callback_handler(int signum);

	void ChangeStatus();

#pragma endregion

#pragma region Variables

	std::string token = "";

	// The bot reference.
	dpp::cluster* botRef;

	// All of BUD-e's statuses!
	const std::vector<std::string> statuses = { "$playing with wires.", "$playing Golf on the moon!", 
	"$listening electro-beeps!", "$listening circuit symphonies!", 
	"$watching binary sunsets!", "$watching algorithms in action!"};

#pragma endregion
};
