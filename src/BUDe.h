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

	dpp::cluster* botRef;

	const std::vector<std::string> statuses = { "$playing with wires.", "$playing Golf on the moon!", 
	"$listening to electro-beeps!", "$listening to circuit symphonies!", 
	"$watching binary sunsets!", "$watching algorithms in action!"};

#pragma endregion
};
