﻿#include "BUDe.h"

int main(int argc, char *argv[])
{

    // "./BUDe" counts as an argument so 2 here means "./BUDe <token>"
	if(argc != 2)
	{
		std::cout << "No bot token specified. Can't launch bot Aborting...";
		return 0;
	}

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
        else if (event.command.get_command_name() == "embedtest")
        {
            event.reply(dpp::message(event.command.channel_id, EmbedBuilder::BasicEmbed(dpp::colours::aqua,
                "This is a test embed.", "If you're seeing this, embeds fully work and are customizable.")));
        }
        else if (event.command.get_command_name() == "lol")
        {
            event.reply(dpp::message(event.command.channel_id, EmbedBuilder::BasicEmbed(dpp::colours::aqua,
                std::get<std::string>(event.get_parameter("title")),
                std::get<std::string>(event.get_parameter("description")))));
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
                std::string("- mysqlconnector\n") +
                std::string("\n") +
                std::string("Again, Thank you for all the support. I love you all and I'm so happy to see you using BUD-e once again.");

            event.reply(dpp::message(event.command.channel_id, EmbedBuilder::BasicEmbed(dpp::colours::aqua,
                "BUD-e - Credits.",
                str)));
        }

    });

    BUDe::botRef->log(dpp::ll_info, "AHHHHHHHHHH.");

    /* Register slash command here in on_ready */
    BUDe::botRef->on_ready([&](const dpp::ready_t& event) {

        BUDe::botRef->log(dpp::ll_info, "Bot is now ready.");

        /* Wrap command registration in run_once to make sure it doesnt run on every full reconnection */
        if (dpp::run_once<struct register_bot_commands>()) {

            BUDe::botRef->log(dpp::ll_info, "Bot is registering commands.");

            dpp::slashcommand lol("lol", "Testing embeds with arguments", BUDe::botRef->me.id);
            dpp::slashcommand announcement("Announcement", "Create an announcement for BUD-e's tower.", BUDe::botRef->me.id);

            lol
                .add_option(dpp::command_option(dpp::co_string, "colour", "The colour of the embed", true))
                .add_option(dpp::command_option(dpp::co_string, "title", "The title of the embed", true))
                .add_option(dpp::command_option(dpp::co_string, "description", "The description of the embed", true));

            announcement
                .add_option(dpp::command_option(dpp::co_string, "title", "The title of the announcement", true))
                .add_option(dpp::command_option(dpp::co_string, "text", "The announcement text", true));

            BUDe::botRef->global_command_create(dpp::slashcommand("ping", "Ping pong!", BUDe::botRef->me.id));
            BUDe::botRef->global_command_create(dpp::slashcommand("pong", "Pong ping!", BUDe::botRef->me.id));
            BUDe::botRef->global_command_create(dpp::slashcommand("credits", "Credits of BUD-e.", BUDe::botRef->me.id));
            BUDe::botRef->guild_command_create(dpp::slashcommand("embedtest", "Testing!", BUDe::botRef->me.id), 695826306180448312);
            BUDe::botRef->guild_command_create(lol, 695826306180448312);
            BUDe::botRef->guild_command_create(announcement, 667401873233543173);
        }

        BUDe::botRef->set_presence(dpp::presence(dpp::presence_status::ps_online, dpp::activity_type::at_custom, "Booting..."));

        std::thread presenceThread(ChangeStatus);

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

void ChangeStatus() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(30));

        BUDe::botRef->set_presence(dpp::presence(dpp::presence_status::ps_online, dpp::activity_type::at_custom, "Testing..."));
    }
}