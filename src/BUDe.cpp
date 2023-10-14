#include "BUDe.h"
#include "Commands/AnnouncementCommand.h"
#include "Commands/PingCommand.h"
#include "Commands/CreditsCommand.h"
#include "Listeners/rps_listener.h"
#include "Commands/AvatarCommand.h"
#include "Listeners/command_listener.h"
#include "Utils/EmbedBuilder.h"
#include "Commands/RPSCommand.h"
#include "Commands/EchoCommand.h"
#include "Commands/MicrowaveCommand.h"
#include "Commands/BallsTugCommand.h"
#include "Commands/MemeCommand.h"
#include <random>
#include <regex>

using json = nlohmann::json;

int main(int argc, char *argv[])
{
	// "./BUDe" counts as an argument so 2 here means "./BUDe <token>"
	if(argc != 2) {
		std::cout << "No bot token specified. Can't launch bot Aborting...";
		return 0;
	}

	BUDe::token = argv[1];

	dpp::cluster bot{BUDe::token, dpp::i_default_intents | dpp::i_message_content};

	BUDe::botRef = &bot;

	BUDe::botRef->on_log(dpp::utility::cout_logger());

	BUDe::commands.emplace_back(std::make_unique<RPSCommand>());
	BUDe::commands.emplace_back(std::make_unique<PingCommand>());
	BUDe::commands.emplace_back(std::make_unique<AnnouncementCommand>());
	BUDe::commands.emplace_back(std::make_unique<CreditsCommand>());
	BUDe::commands.emplace_back(std::make_unique<AvatarCommand>());
	BUDe::commands.emplace_back(std::make_unique<EchoCommand>());
	BUDe::commands.emplace_back(std::make_unique<MicrowaveCommand>());
	BUDe::commands.emplace_back(std::make_unique<BallsTugCommand>());
	BUDe::commands.emplace_back(std::make_unique<MemeCommand>());

	bot.on_slashcommand(command_listener::on_slashcommand);
	bot.on_button_click(rps_listener::on_button_click);

	/* Register slash command here in on_ready */
	BUDe::botRef->on_ready([&](const dpp::ready_t& event) {

		/* Wrap command registration in run_once to make sure it doesn't run on every full reconnection */
		if (dpp::run_once<struct register_bot_commands>()) {

			BUDe::botRef->log(dpp::ll_info, "Bot is registering commands.");

			std::vector<dpp::slashcommand> tempCommands;
			std::vector<dpp::slashcommand> tempCommandsPrivate;

			for(auto& cmd : BUDe::commands)
			{
				dpp::slashcommand tempCommand{cmd->commandName, cmd->commandDescription, BUDe::botRef->me.id};

				for(dpp::command_option& option : cmd->CommandOptions())
				    	tempCommand.add_option(option);

			    	tempCommand.set_default_permissions(cmd->commandPermission);

				if(cmd->Private()) // If command is private add to private list.
				    	tempCommandsPrivate.emplace_back(tempCommand);
				else // otherwise, add to normal commands.
				    	tempCommands.emplace_back(tempCommand);
			}

			// Bulk create because otherwise we'll get nuked by rate limits.
			BUDe::botRef->global_bulk_command_create(tempCommands);

			BUDe::botRef->guild_bulk_command_create(tempCommandsPrivate, 667401873233543173);

			BUDe::botRef->log(dpp::ll_info, "Bot has completed registering commands.");

			bot.start_timer([](const dpp::timer& timer) {
			    	BUDe::DoStatusChange();
			}, 120);
		}

		BUDe::botRef->message_create(dpp::message(667405048267014164,
		    EmbedBuilder::BasicEmbedWithTimestamp(dpp::colours::green,
			"All systems are online, Captain!",
			"All systems have booted online and are ready to go!")));

		BUDe::botRef->log(dpp::ll_info, "BUD-e is now ready.");

		// Call status change now.
		BUDe::DoStatusChange();
	});

	signal(SIGINT, BUDe::callback_handler);
	signal(SIGTERM, BUDe::callback_handler);

	/* Start the bot */
	BUDe::botRef->start(dpp::st_wait);

	return 0;
}

void BUDe::callback_handler(int signum)
{
	BUDe::botRef->message_create(dpp::message(667405048267014164,EmbedBuilder::BasicEmbedWithTimestamp(
		dpp::colours::red,
		"Shutting systems off, Captain!",
		"I have received a signal to shut down. "))
	);

	// Safely shut down the bot, meaning the bot actually shuts down when this stops rather than us leaving it in limbo.
	BUDe::botRef->shutdown();
	exit(signum);
}

void BUDe::DoStatusChange() {
	// Generate a random value in the statuses array.
	std::random_device rd;
	std::mt19937 gen{rd()};
	std::uniform_int_distribution<> distrib(0, statuses.size() - 1);

	std::string newStatus{statuses[distrib(gen)]};

	dpp::activity_type type = dpp::activity_type::at_game;

	if(newStatus.find("$listening") != std::string::npos) {
	    	newStatus = std::regex_replace(newStatus, std::regex("\\$listening "), "");
	    	type = dpp::activity_type::at_listening;
	} else if(newStatus.find("$playing") != std::string::npos) {
	    	newStatus = std::regex_replace(newStatus, std::regex("\\$playing "), "");
	    	type = dpp::activity_type::at_game;
	} else if(newStatus.find("$watching") != std::string::npos) {
	    	newStatus = std::regex_replace(newStatus, std::regex("\\$watching "), "");
	    	type = dpp::activity_type::at_watching;
	}

	// Get a random status message and set the bot's presence to it.
	BUDe::botRef->set_presence(dpp::presence{dpp::presence_status::ps_online, type, newStatus});
}