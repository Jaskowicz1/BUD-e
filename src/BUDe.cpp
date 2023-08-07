#include "BUDe.h"
#include <random>
#include <regex>

int main(int argc, char *argv[])
{
    // "./BUDe" counts as an argument so 2 here means "./BUDe <token>"
	if(argc != 2)
	{
		std::cout << "No bot token specified. Can't launch bot Aborting...";
		return 0;
	}

    /*
    event.reply(dpp::message(event.command.channel_id, EmbedBuilder::BasicEmbed(dpp::colours::aqua,
                std::get<std::string>(event.get_parameter("title")),
                std::get<std::string>(event.get_parameter("description")))));
    */

	BUDe::token = argv[1];
	
	dpp::cluster bot(BUDe::token);

    BUDe::botRef = &bot;

    BUDe::botRef->on_log(dpp::utility::cout_logger());

    BUDe::botRef->on_slashcommand([&](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "ping") {
            event.reply("Pong!");
        }
        else if (event.command.get_command_name() == "pong") {
            event.reply("Ping!");
        }
        else if (event.command.get_command_name() == "rps" || event.command.get_command_name() == "rockpaperscissors") {
            event.reply(dpp::message(event.command.channel_id, "test")
            .add_component(
                dpp::component().set_label("Rock").
                set_emoji(u8"🪨").
                set_style(dpp::cos_secondary).
                set_id("rock")
            )
            .add_component(
                dpp::component().set_label("Paper").
                set_emoji(u8"📰").
                set_style(dpp::cos_secondary).
                set_id("paper")
            ).add_component(
                dpp::component().set_label("Scissors").
                set_emoji(u8"✂️").
                set_style(dpp::cos_secondary).
                set_id("scissors")
            ));
        }
        else if (event.command.get_command_name() == "announcement")
        {
            BUDe::botRef->message_create(dpp::message(667402621333798923, EmbedBuilder::BasicEmbed(dpp::colours::aqua,
                std::get<std::string>(event.get_parameter("title")),
                std::get<std::string>(event.get_parameter("text")))));

            event.reply("Announcement has been sent.");
        }
        else if (event.command.get_command_name() == "credits")
        {
            std::string str;

            str = std::string("Thank you for using BUD-e! I greatly appreciate it and, from the bottom of my heart, I love you.\n") +
                std::string("\n") +
                std::string("Creator & Developer - Archie Jaskowicz (@JaskowiczArchie, jaskowicz)\n") +
                std::string("BUD-e's Discord - https://bude.rocketeersgaming.net\n") +
                std::string("Rocketeers Discord - https://discord.rocketeersgaming.net\n") +
                std::string("Add BUD-e to another server - https://basicutilitydroid.io\n") +
                std::string("\n") +
                std::string("APIs used:\n") +
                std::string("- D++\n") +
                std::string("\n") +
                std::string("Again, Thank you for all the support. I love you all and I'm so happy to see you using BUD-e once again.");

            event.reply(dpp::message(event.command.channel_id, EmbedBuilder::BasicEmbed(dpp::colours::aqua,
                "BUD-e - Credits.",
                str)));
        }

    });

    /* Register slash command here in on_ready */
    BUDe::botRef->on_ready([&](const dpp::ready_t& event) {

        BUDe::botRef->log(dpp::ll_info, "Bot is now ready.");

        /* Wrap command registration in run_once to make sure it doesnt run on every full reconnection */
        if (dpp::run_once<struct register_bot_commands>()) {

            BUDe::botRef->log(dpp::ll_info, "Bot is registering commands.");

            // ---------------------------------------------------------------------------------------
            // All global commands.

            dpp::slashcommand ping("ping", "Ping pong!", BUDe::botRef->me.id);
            dpp::slashcommand pong("pong", "Pong ping!", BUDe::botRef->me.id);
            dpp::slashcommand credits("credits", "Credits of BUD-e.", BUDe::botRef->me.id);

            // Bulk create because otherwise we'll get nuked by rate limits.
            BUDe::botRef->global_bulk_command_create({ping, pong, credits});

            // ---------------------------------------------------------------------------------------
            // All guild commands just for BUD-e's Tower.

            dpp::slashcommand rps("rps", "Play Rock, Paper, Scissors!", BUDe::botRef->me.id);
            dpp::slashcommand announcement("announcement", "Create an announcement for BUD-e's tower.", BUDe::botRef->me.id);

            /*
            embedtesttwo
                .add_option(dpp::command_option(dpp::co_string, "colour", "The colour of the embed", true))
                .add_option(dpp::command_option(dpp::co_string, "title", "The title of the embed", true))
                .add_option(dpp::command_option(dpp::co_string, "description", "The description of the embed", true));
                */

            announcement
                .add_option(dpp::command_option(dpp::co_string, "title", "The title of the announcement", true))
                .add_option(dpp::command_option(dpp::co_string, "text", "The announcement text", true));

            BUDe::botRef->guild_bulk_command_create({rps, announcement}, 667401873233543173);

            BUDe::botRef->log(dpp::ll_info, "Bot has completed registering commands.");
        }

        // Message for status here doesn't matter, won't get sent anyways.
        BUDe::botRef->set_presence(dpp::presence(dpp::presence_status::ps_online, dpp::activity_type::at_custom, ""));

        // Create a thread to handle all the status changing.
        std::thread presenceThread(BUDe::ChangeStatus);

        // Turn into daemon process so it's not reliant on main thread.
        // We never have to communicate with this thread so it's okay.
        presenceThread.detach();

        BUDe::botRef->message_create(dpp::message(667405048267014164,
            EmbedBuilder::BasicEmbedWithTimestamp(dpp::colours::green,
                "All systems are online, Captain!",
                "All systems have booted online and are ready to go!")));
    });

    BUDe::botRef->on_presence_update([&](const dpp::presence_update_t& event) {
        std::cout << "Presence updated. New presence is: " << event.rich_presence.status();
        });

    signal(SIGINT, BUDe::callback_handler);

    /* Start the bot */
    BUDe::botRef->start(dpp::st_wait);

    return 0;
}

void BUDe::callback_handler(int signum)
{
    BUDe::botRef->shutdown();
    exit(signum);
}

void BUDe::ChangeStatus() {

    while (true) {
        // Once every five minutes, don't want it changing too fast (Rate-Limit reasons and because it'd be silly).
        std::this_thread::sleep_for(std::chrono::minutes(5));

        // Generate a random value in the statuses array.
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, statuses.size() - 1);

        std::string newStatus (statuses[distrib(gen)]);

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
        
        newStatus = std::regex_replace(newStatus, std::regex("\\$servers"), "" + BUDe::botRef->current_user_get_guilds_sync().size());

        // Get a random status message and set the bot's presence to it.
        BUDe::botRef->set_presence(dpp::presence(dpp::presence_status::ps_online, type, newStatus));
    }
}