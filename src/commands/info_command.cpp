#include "commands/info_command.h"

#include <utils/database.h>

#include "BUDe.h"

int64_t proc_self_value(const std::string& find_token) {
	int64_t ret = 0;
	std::ifstream self_status("/proc/self/status");
	while (self_status) {
		std::string token;
		self_status >> token;
		if (token == find_token) {
			self_status >> ret;
			break;
		}
	}
	self_status.close();
	return ret;
}

int64_t rss() {
	return proc_self_value("VmRSS:") * 1024;
}

dpp::coroutine<void> info_command::execute(dpp::slashcommand_t event) {

	dpp::embed embed = dpp::embed()
			.set_url("https://basicutilitydroid.io/")
			.set_title("BUD-e Information")
			.set_footer(dpp::embed_footer{
				.text = "Requested by " + event.command.usr.format_username(),
				.icon_url = BUDe::botRef->me.get_avatar_url(),
				.proxy_url = "",
			})
			.set_colour(0x7aff7a)
			//.set_thumbnail("https://beholder.cc/img/beholder_animated.gif")
			//.set_description(has_premium ? ":star: This server has Beholder Premium! :star:" : "")
			.add_field("Bot Uptime", BUDe::botRef->uptime().to_string(), true)
			.add_field("Memory Usage", std::to_string(rss() / 1024 / 1024) + "M", true)
			.add_field("Total Servers", std::to_string(dpp::get_guild_cache()->count()), true)
			//.add_field("Log Channel", log_channel.length() ? "<#" + log_channel + ">" : "(not set)", true)
			.add_field("SQL cache size", std::to_string(db::cache_size()), true)
			.add_field("SQL query count", std::to_string(db::query_count()), true);

	embed.add_field("Library Version", "[" + std::string(DPP_VERSION_TEXT) + "](https://dpp.dev/)", false);

	co_return event.reply(dpp::message().add_embed(embed));
}
