#pragma once

#include "commands/command.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include "dpp/dpp.h"

namespace BUDe
{

#pragma region Functions

void callback_handler(int signum);

void DoStatusChange();

#pragma endregion

#pragma region Variables

// The bot reference.
inline dpp::cluster* botRef;

inline bool register_commands;

// All of BUD-e's statuses!
inline const std::vector<std::string> statuses = { "$playing with wires.",
						   "$playing Golf on the moon!",
						   "$listening electro-beeps!",
						   "$listening circuit symphonies!",
						   "$watching binary sunsets!",
						   "$watching algorithms in action!" };

inline std::vector<std::unique_ptr<command>> commands;

#pragma endregion
};
