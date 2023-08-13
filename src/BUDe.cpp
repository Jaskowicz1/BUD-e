#include "BUDe.h"
#include "Commands/AnnouncementCommand.h"
#include "Commands/PongCommand.h"
#include "Commands/PingCommand.h"
#include "Commands/CreditsCommand.h"
#include "Listeners/RPSListener.h"
#include "Listeners/HighFiveListener.h"
#include "Commands/ServerInfoCommand.h"
#include "Commands/AvatarCommand.h"
#include "Commands/AttachmentCommand.h"
#include "Commands/EmbedCommand.h"
#include "Commands/ButtonCommand.h"
#include "Commands/MathCommand.h"
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

    BUDe::commands.emplace_back(std::make_unique<RPSCommand>());
    BUDe::commands.emplace_back(std::make_unique<PingCommand>());
    BUDe::commands.emplace_back(std::make_unique<PongCommand>());
    BUDe::commands.emplace_back(std::make_unique<AnnouncementCommand>());
    BUDe::commands.emplace_back(std::make_unique<CreditsCommand>());
    BUDe::commands.emplace_back(std::make_unique<ServerInfoCommand>());
    BUDe::commands.emplace_back(std::make_unique<AvatarCommand>());
    BUDe::commands.emplace_back(std::make_unique<AttachmentCommand>());
    BUDe::commands.emplace_back(std::make_unique<EmbedCommand>());
    BUDe::commands.emplace_back(std::make_unique<ButtonCommand>());
    BUDe::commands.emplace_back(std::make_unique<MathCommand>());

    BUDe::botRef->on_slashcommand([&](const dpp::slashcommand_t& event) {
        for(auto& cmd : BUDe::commands) {
            if(cmd->commandName == event.command.get_command_name()) {
                // The command was right, but it's disabled, so we just want to break the for loop.
                // or, the command is private and the user executing the command isn't me.
                if(!cmd->Enabled() || (cmd->Private() && event.command.usr.id.str() != "447098177879932939"))
                    break;

                cmd->Execute(event);
                break;
            }
        }
    });

    BUDe::botRef->on_button_click(&RPSListener::OnButtonClick);
    BUDe::botRef->on_user_context_menu(&HighFiveListener::OnUserContextMenu);

    BUDe::botRef->on_button_click([&bot](const dpp::button_click_t& event) {
        /* Button clicks are still interactions, and must be replied to in some form to
         * prevent the "this interaction has failed" message from Discord to the user.
         */
        if(event.custom_id == "myid")
            event.reply("You clicked: " + event.custom_id);
    });

    bot.on_button_click([&bot](const dpp::button_click_t & event) {
        if (event.custom_id == "10") {
            event.reply(dpp::message("You got it right!").set_flags(dpp::m_ephemeral));
        } else {
            event.reply(dpp::message("Wrong! Try again.").set_flags(dpp::m_ephemeral));
        }
    });

    /* Register slash command here in on_ready */
    BUDe::botRef->on_ready([&](const dpp::ready_t& event) {

        /* Wrap command registration in run_once to make sure it doesn't run on every full reconnection */
        if (dpp::run_once<struct register_bot_commands>()) {

            BUDe::botRef->log(dpp::ll_info, "Bot is registering commands.");

            std::vector<dpp::slashcommand> tempCommands;
            std::vector<dpp::slashcommand> tempCommandsPrivate;

            dpp::slashcommand command;
            command.set_name("High Five");
            command.set_application_id(bot.me.id);

            command.set_type(dpp::ctxm_user);

            // JUST TEMP FOR D++ DOCS.
            tempCommandsPrivate.push_back(command);

            for(auto& cmd : BUDe::commands)
            {
                dpp::slashcommand tempCommand(cmd->commandName, cmd->commandDescription, BUDe::botRef->me.id);

                for(dpp::command_option& option : cmd->CommandOptions())
                    tempCommand.add_option(option);

                if(cmd->Private()) // If command is private add to private list.
                    tempCommandsPrivate.emplace_back(tempCommand);
                else // otherwise, add to normal commands.
                    tempCommands.emplace_back(tempCommand);
            }

            // Bulk create because otherwise we'll get nuked by rate limits.
            BUDe::botRef->global_bulk_command_create(tempCommands);

            BUDe::botRef->guild_bulk_command_create(tempCommandsPrivate, 667401873233543173);

            BUDe::botRef->log(dpp::ll_info, "Bot has completed registering commands.");
        }

        // Message for status here doesn't matter, won't get sent anyway.
        BUDe::botRef->set_presence(dpp::presence(dpp::presence_status::ps_online, dpp::activity_type::at_custom, ""));

        // Create a thread to handle all the status changing.
        std::thread presenceThread(BUDe::ChangeStatusThread);

        // Turn into daemon process, so it's not reliant on main thread.
        // We never have to communicate with this thread, so it's okay.
        presenceThread.detach();

        BUDe::botRef->message_create(dpp::message(667405048267014164,
            EmbedBuilder::BasicEmbedWithTimestamp(dpp::colours::green,
                "All systems are online, Captain!",
                "All systems have booted online and are ready to go!")));

        BUDe::botRef->log(dpp::ll_info, "BUD-e is now ready.");
    });

    signal(SIGINT, BUDe::callback_handler);
    signal(SIGTERM, BUDe::callback_handler);

    /* Start the bot */
    BUDe::botRef->start(dpp::st_wait);

    return 0;
}

void BUDe::callback_handler(int signum)
{
    BUDe::botRef->message_create(dpp::message(667405048267014164,
        EmbedBuilder::BasicEmbedWithTimestamp(dpp::colours::red,
            "Shutting systems off, Captain!",
            "I have received a signal to shut down. ")));

    // Safely shut down the bot, meaning the bot actually shuts down when this stops rather than us leaving it in limbo.
    BUDe::botRef->shutdown();
    exit(signum);
}

void BUDe::ChangeStatusThread() {

    std::this_thread::sleep_for(std::chrono::seconds(10));
    // Change status here, so we don't end up with 5 minutes of no status.
    DoStatusChange();

    while (true) {
        // Once every five minutes, don't want it changing too fast (Rate-Limit reasons and because it'd be silly).
        std::this_thread::sleep_for(std::chrono::minutes(5));

        DoStatusChange();
    }
}

void BUDe::DoStatusChange() {
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

    // Get a random status message and set the bot's presence to it.
    BUDe::botRef->set_presence(dpp::presence(dpp::presence_status::ps_online, type, newStatus));
}