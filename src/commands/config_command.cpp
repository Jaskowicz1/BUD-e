#include "commands/config_command.h"
#include "utils/embed_builder.h"
#include "utils/database.h"

dpp::coroutine<void> config_command::execute(dpp::slashcommand_t event) {

	if (std::holds_alternative<std::monostate>(event.get_parameter("config_setting"))) {
		event.reply("No setting was provided! Please provide a setting to change.");
		co_return;
	}

	auto setting = std::get<std::string>(event.get_parameter("config_setting"));

	if(setting == "modlog_channel") {
		dpp::component select_menu;
		select_menu.set_type(dpp::cot_channel_selectmenu)
			.set_placeholder("Pick the channel for mod logs!")
			.set_id("select_modlog_channel");

		event.reply(dpp::message("Pick the channel for mod logs to be sent to:").add_component(dpp::component().add_component(select_menu)));
	} else {
		event.reply("Invalid setting! Please provide a setting to change.");
	}
}

std::vector<dpp::command_option> config_command::command_options() {
	std::vector<dpp::command_option> temp;
	temp.emplace_back(dpp::co_string, "config_setting", "The setting to modify", true).set_auto_complete(true);
	return temp;
}

config_command::config_command(dpp::cluster& bot) : command("config", "Set the configs for your server") {
	bot.on_select_click([&bot](const dpp::select_click_t& event) {

	});

	bot.on_autocomplete([&bot](const dpp::autocomplete_t& event) {
		for(auto& opt : event.options) {
			if(opt.focused) {
				if(opt.name == "config_setting") {
					dpp::interaction_response response{dpp::ir_autocomplete_reply};
					response.add_autocomplete_choice(dpp::command_option_choice("Modlog Channel", "modlog_channel"));
					response.add_autocomplete_choice(dpp::command_option_choice("flags", "flags"));
					bot.interaction_response_create(event.command.id, event.command.token, response);
				}
			}
		}
	});
}
