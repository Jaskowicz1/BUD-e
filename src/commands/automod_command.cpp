#include "commands/automod_command.h"
#include "utils/embed_builder.h"
#include "utils/database.h"

dpp::coroutine<void> automod_command::execute(dpp::slashcommand_t event) {

	if (std::holds_alternative<std::monostate>(event.get_parameter("automod_setting"))) {
		event.reply("No setting was provided! Please provide a setting to change.");
		co_return;
	}

	auto setting = std::get<std::string>(event.get_parameter("automod_setting"));

	if(setting == "flags") {
		dpp::component select_menu;
		select_menu.set_type(dpp::cot_selectmenu)
			.set_placeholder("Pick the automod features")
			.set_min_values(0)
			.set_max_values(3)
			.set_id("select_automod_flags");

		select_menu.add_select_option(dpp::select_option("Capital Spam", "caps", "Prevent too many capitals in a message"))
		.add_select_option(dpp::select_option("Links", "links", "Prevent links being sent in a message"))
		.add_select_option(dpp::select_option("Message Spam", "spam", "Prevent users sending a message 10 times during a 5 second span (2 messages every second)."));

		event.reply(dpp::message("Select what the automod should detect:").add_component(dpp::component().add_component(select_menu)));
	} else {
		event.reply("Invalid setting! Please provide a setting to change.");
	}
}

std::vector<dpp::command_option> automod_command::command_options() {
	std::vector<dpp::command_option> temp;
	temp.emplace_back(dpp::co_string, "automod_setting", "The setting to modify", true).set_auto_complete(true);
	return temp;
}

automod_command::automod_command(dpp::cluster& bot) : command("automod", "Set the channel/flags for the automod system.") {
	bot.on_select_click([&bot](const dpp::select_click_t& event) {
		if (event.custom_id == "select_automod_flags") {
			uint8_t new_flags{};

			if(event.values.empty()) {
				new_flags = 0;
			} else {
				for(const std::string& value : event.values) {
					if(value == "caps") {
						new_flags |= am_caps;
					} else if(value == "links") {
						new_flags |= am_links;
					} else if(value == "spam") {
						new_flags |= am_spam;
					}
				}
			}

			db::transaction();
			db::query("UPDATE servers SET automod_flags = ? WHERE guild_id = ?", { new_flags, event.command.guild_id });

			if (!db::error().empty()) {
				/* We get out the transaction in the event of a failure. */
				db::rollback();
				event.reply(dpp::message("❌ Failed to set automod flags").set_flags(dpp::m_ephemeral));
				return;
			}

			db::commit();
			event.reply(dpp::message("✅ Automod flags set").set_flags(dpp::m_ephemeral));
		}
	});

	bot.on_autocomplete([&bot](const dpp::autocomplete_t& event) {
		for(auto& opt : event.options) {
			if(opt.focused) {
				if(opt.name == "automod_setting") {
					dpp::interaction_response response{dpp::ir_autocomplete_reply};
					response.add_autocomplete_choice(dpp::command_option_choice("channel", "channel"));
					response.add_autocomplete_choice(dpp::command_option_choice("flags", "flags"));
					bot.interaction_response_create(event.command.id, event.command.token, response);
				}
			}
		}
	});
}
