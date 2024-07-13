#include "BUDe.h"
#include "commands/announcement_command.h"
#include "commands/ping_command.h"
#include "commands/credits_command.h"
#include "listeners/rps_listener.h"
#include "commands/avatar_command.h"
#include "listeners/command_listener.h"
#include "utils/embed_builder.h"
#include "commands/rps_command.h"
#include "commands/echo_command.h"
#include "commands/microwave_command.h"
#include "commands/ballstug_command.h"
#include "commands/meme_command.h"
#include "utils/config.h"
#include "utils/database.h"
#include "commands/automod_command.h"
#include <random>
#include <regex>
#include <commands/info_command.h>

using json = nlohmann::json;

int main(int argc, char *argv[]) {
	if (argc == 2 && strcmp(argv[1], "REGISTER") == 0) {
		std::cout << "Registering commands..." << "\n";
		BUDe::register_commands = true;
	}

	config::init("../config.json");

	dpp::cluster bot{
		config::get("token"),
		dpp::i_default_intents | dpp::i_message_content,
		config::get("shards")
	};

	BUDe::botRef = &bot;

	BUDe::botRef->on_log(dpp::utility::cout_logger());

	bot.set_websocket_protocol(dpp::ws_etf);

	BUDe::commands.emplace_back(std::make_unique<rps_command>());
	BUDe::commands.emplace_back(std::make_unique<ping_command>());
	BUDe::commands.emplace_back(std::make_unique<announcement_command>());
	BUDe::commands.emplace_back(std::make_unique<credits_command>());
	BUDe::commands.emplace_back(std::make_unique<avatar_command>());
	BUDe::commands.emplace_back(std::make_unique<echo_command>());
	BUDe::commands.emplace_back(std::make_unique<microwave_command>());
	BUDe::commands.emplace_back(std::make_unique<ballstug_command>());
	BUDe::commands.emplace_back(std::make_unique<meme_command>());
	BUDe::commands.emplace_back(std::make_unique<automod_command>(bot));
	BUDe::commands.emplace_back(std::make_unique<info_command>());

	bot.on_slashcommand(command_listener::on_slashcommand);
	bot.on_button_click(rps_listener::on_button_click);

	/* Register slash command here in on_ready */
	BUDe::botRef->on_ready([&bot](const dpp::ready_t& event) {

		for(dpp::snowflake server : event.guilds) {
			db::resultset server_list = db::query("SELECT guild_id FROM servers WHERE guild_id = ?", {server});

			if(server_list.empty()) {
				db::query("INSERT INTO servers (guild_id) VALUES(?)", { server });
			}
		}

		/* Wrap command registration in run_once to make sure it doesn't run on every full reconnection */
		if (BUDe::register_commands && dpp::run_once<struct register_bot_commands>()) {

			BUDe::botRef->log(dpp::ll_info, "Bot is registering commands.");

			std::vector<dpp::slashcommand> tempCommands;
			std::vector<dpp::slashcommand> tempCommandsPrivate;

			for (auto& cmd : BUDe::commands) {
				dpp::slashcommand tempCommand{cmd->command_name, cmd->command_description, BUDe::botRef->me.id};

				for(dpp::command_option& option : cmd->command_options())
				    	tempCommand.add_option(option);

			    	tempCommand.set_default_permissions(cmd->command_permission);

				if(cmd->is_private()) // If command is private add to private list.
				    	tempCommandsPrivate.emplace_back(tempCommand);
				else // otherwise, add to normal commands.
				    	tempCommands.emplace_back(tempCommand);
			}

			// Bulk create because otherwise we'll get nuked by rate limits.
			BUDe::botRef->global_bulk_command_create(tempCommands);

			BUDe::botRef->guild_bulk_command_create(tempCommandsPrivate, 667401873233543173);

			BUDe::botRef->log(dpp::ll_info, "Bot has completed registering commands.");
		}

		if(config::get("announce_state")) {
			BUDe::botRef->message_create(
				dpp::message{667405048267014164,embed_builder::basic_embed_with_timestamp(dpp::colours::green,
													  "All systems are online, Captain!",
													  "All systems have booted online and are ready to go!")
				}
			);
		}

		BUDe::botRef->log(dpp::ll_info, "BUD-e is now ready.");

		// Call status change now.
		BUDe::DoStatusChange();

		/* Now, start a timer to do a status change every x seconds */
		bot.start_timer([](const dpp::timer& timer) {
			BUDe::DoStatusChange();
		}, 120);
	});

	signal(SIGINT, BUDe::callback_handler);
	signal(SIGTERM, BUDe::callback_handler);

	db::init(bot);

	/* Start the bot */
	BUDe::botRef->start(dpp::st_wait);

	return 0;
}

void BUDe::callback_handler(int signum) {
	if(config::get("announce_state")) {
		BUDe::botRef->message_create(dpp::message(667405048267014164, embed_builder::basic_embed_with_timestamp(
			dpp::colours::red,
			"Shutting systems off, Captain!",
			"I have received a signal to shut down. "))
		);
	}

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

	if (newStatus.find("$listening") != std::string::npos) {
	    	newStatus = std::regex_replace(newStatus, std::regex("\\$listening "), "");
	    	type = dpp::activity_type::at_listening;
	} else if (newStatus.find("$playing") != std::string::npos) {
	    	newStatus = std::regex_replace(newStatus, std::regex("\\$playing "), "");
	    	type = dpp::activity_type::at_game;
	} else if (newStatus.find("$watching") != std::string::npos) {
	    	newStatus = std::regex_replace(newStatus, std::regex("\\$watching "), "");
	    	type = dpp::activity_type::at_watching;
	}

	// Get a random status message and set the bot's presence to it.
	BUDe::botRef->set_presence(dpp::presence{dpp::presence_status::ps_online, type, newStatus});
}