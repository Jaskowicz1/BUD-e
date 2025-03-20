#include "commands/meme_command.h"

#include "BUDe.h"

dpp::coroutine<void> meme_command::execute(dpp::slashcommand_t event) {

	co_await event.co_thinking(false);

	// We can safely assume that there will always be something as it's a required input.
	auto top_text = std::get<std::string>(event.get_parameter("toptext"));
	auto bottom_text = std::get<std::string>(event.get_parameter("bottomtext"));
	auto image_url = std::get<std::string>(event.get_parameter("imageurl"));

	std::string url = "https://api.memegen.link/images/custom/" + top_text + "/" + bottom_text + ".jpg?alt=" + image_url;

	dpp::http_request_completion_t request = co_await BUDe::botRef->co_request(url, dpp::m_get);

	dpp::message msg{""};
	if (request.status == 200) {
		msg.add_file("meme.png", request.body);
	} else {
		event.edit_response("Failed to generate a meme! Please make sure that your top text, bottom text, and image url, are valid!");
		co_return;
	}

	co_return event.edit_response(msg);
}
