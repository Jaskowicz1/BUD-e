#pragma once

#include "command.h"

enum automod_flags : uint8_t {
	/**
	 * @brief If message contains too many caps.
	 */
	am_caps 	= 0b00000001,

	/**
	 * @brief If message contains links
	 */
	am_links 	= 0b00000010,

	/**
	 * @brief If user has sent a message 10 times during a 5 second span (2 messages every second).
	 */
	am_spam		= 0b00000100,
};

/**
 * @brief The response that automod should respond with.
 *
 * @note automod will ALWAYS delete the message that flagged.
 */
enum automod_response : uint8_t {
	/**
	 * @brief If message contains too many caps.
	 */
	amr_warn 		= 0b00000001,

	/**
	 * @brief If message contains links
	 */
	amr_multi_offence_mute 	= 0b00000010,

	/**
	 * @brief If user has sent a message 10 times during a 5 second span (2 messages every second).
	 */
	amr_multi_offence_ban	= 0b00000100,

	/**
	 * @brief If message contains links
	 */
	amr_instant_mute 	= 0b00000010,

	/**
	 * @brief If user has sent a message 10 times during a 5 second span (2 messages every second).
	 */
	amr_instant_ban		= 0b00000100,
};

class automod_command : public command {

public:

	explicit automod_command(dpp::cluster& bot);

	dpp::coroutine<void> execute(dpp::slashcommand_t event) override;

	std::vector<dpp::command_option> command_options() override;

	bool is_enabled() override {
		return true;
	}

	bool is_private() override {
		return true;
	}

};