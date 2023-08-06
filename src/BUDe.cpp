#include "BUDe.h"

int main(int argc, char *argv[])
{

	if(argc != 1)
	{
		std::cout << "\033[41" << "No bot token specified. Can't launch bot. Aborting...";
		return 0;
	}

	token = argv[0];
	
	dpp::cluster bot(token);

	bot.on_log(dpp::utility::cout_logger());

    bot.on_ready([&bot](const dpp::ready_t& event) {

        bot.log(dpp::ll_info, "Bot is now ready.");

        bot.set_presence(dpp::presence(dpp::presence_status::ps_online, dpp::activity_type::at_custom, "Rebooting..."));

        bot.message_create(dpp::message(667405048267014164,
            EmbedBuilder::BasicEmbedWithTimestamp(dpp::colours::green,
                "All systems are online, Captain!",
                "All systems have booted online and are ready to go!")));
        });

    /* Start the bot */
    bot.start(dpp::st_wait);

    return 0;
}
