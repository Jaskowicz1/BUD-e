#include "commands/credits_command.h"
#include "utils/embed_builder.h"

dpp::coroutine<void> credits_command::execute(dpp::slashcommand_t event) {
	std::string str;

	str = std::string("Thank you for using BUD-e! I greatly appreciate it!\n") +
	      std::string("\n") +
	      std::string("Creator & Developer - Archie Jaskowicz (@JaskowiczArchie, jaskowicz)\n") +
	      std::string("BUD-e's Discord - https://bude.rocketeersgaming.net\n") +
	      std::string("Rocketeers Discord - https://discord.rocketeersgaming.net\n") +
	      std::string("Add BUD-e to another server - https://basicutilitydroid.io\n") +
	      std::string("\n") +
	      std::string("APIs used:\n") +
	      std::string("- D++\n") +
	      std::string("\n") +
	      std::string("Extra thanks to the people over at the D++ discord for the help!") +
	      std::string("\n") +
	      std::string("Again, Thank you for all the support and thank you for using BUD-e!");

	co_return event.reply(
		dpp::message{
			event.command.channel_id,
			embed_builder::basic_embed(dpp::colours::aqua, "BUD-e - Credits.", str)
		}.set_flags(dpp::m_ephemeral)
	);
}
