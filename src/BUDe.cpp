#include "BUDe.h"

int main(int argc, char *argv[])
{

    // "./BUDe" counts as an argument so 2 here means "./BUDe <token>"
	if(argc != 2)
	{
		std::cout << "No bot token specified. Can't launch bot. Aborting...";
		return 0;
	}

	BUDe::token = argv[1];
	
	dpp::cluster bot(BUDe::token);

	bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
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
            bot.message_create(dpp::message(667402621333798923, EmbedBuilder::BasicEmbed(dpp::colours::aqua,
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

    bot.log(dpp::ll_info, "AHHHHHHHHHH.");

    /* Register slash command here in on_ready */
    bot.on_ready([&bot](const dpp::ready_t& event) {

        bot.log(dpp::ll_info, "Bot is now ready.");

        /* Wrap command registration in run_once to make sure it doesnt run on every full reconnection */
        if (dpp::run_once<struct register_bot_commands>()) {

            bot.log(dpp::ll_info, "Bot is registering commands.");

            dpp::slashcommand lol("lol", "Testing embeds with arguments", bot.me.id);
            dpp::slashcommand announcement("Announcement", "Create an announcement for BUD-e's tower.", bot.me.id);

            lol
                .add_option(dpp::command_option(dpp::co_string, "colour", "The colour of the embed", true))
                .add_option(dpp::command_option(dpp::co_string, "title", "The title of the embed", true))
                .add_option(dpp::command_option(dpp::co_string, "description", "The description of the embed", true));

            announcement
                .add_option(dpp::command_option(dpp::co_string, "title", "The title of the announcement", true))
                .add_option(dpp::command_option(dpp::co_string, "text", "The announcement text", true));

            bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
            bot.global_command_create(dpp::slashcommand("pong", "Pong ping!", bot.me.id));
            bot.global_command_create(dpp::slashcommand("credits", "Credits of BUD-e.", bot.me.id));
            bot.guild_command_create(dpp::slashcommand("embedtest", "Testing!", bot.me.id), 695826306180448312);
            bot.guild_command_create(lol, 695826306180448312);
            bot.guild_command_create(announcement, 667401873233543173);
        }

        bot.set_presence(dpp::presence(dpp::presence_status::ps_online, dpp::activity_type::at_custom, "Rebooting..."));

        bot.message_create(dpp::message(667405048267014164,
            EmbedBuilder::BasicEmbedWithTimestamp(dpp::colours::green,
                "All systems are online, Captain!",
                "All systems have booted online and are ready to go!")));
    });

    bot.on_presence_update([&bot](const dpp::presence_update_t& event) {
        std::cout << "Presence updated. New presence is: " << event.rich_presence.status();
        });

    /* Start the bot */
    bot.start(dpp::st_wait);

    return 0;
}
