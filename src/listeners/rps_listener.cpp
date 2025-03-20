#include "listeners/rps_listener.h"
#include <dpp/unicode_emoji.h>
#include <random>
#include "utils/embed_builder.h"
#include "utils/component_builder.h"

dpp::task<void> rps_listener::on_button_click(dpp::button_click_t event) {

    // Handle playing again.
    if(event.custom_id == "playagain") {
        dpp::message msg(event.command.channel_id,
			 embed_builder::basic_embed(dpp::colours::aqua,
						   "Rock, Paper Scissors!",
						   "Let's play rock, paper, scissors! You pick and I'll pick!")
        );

        // this is now nice :)
        component_builder::add_buttons_to_message(msg, {
		component_data{ "Rock", "rock", dpp::unicode_emoji::rock },
		component_data{ "Paper", "paper", dpp::unicode_emoji::newspaper },
		component_data{ "Scissors", "scissors", dpp::unicode_emoji::scissors }
	});

        event.reply(dpp::ir_update_message, msg);

        co_return;
    }

    // If the event wasn't rock, nor paper, nor scissors, then just return.
    // This handler is not made for anything else, and we've already handled playing again (if that was the case).
    if (event.custom_id != "rock" && event.custom_id != "paper" && event.custom_id != "scissors") {
        co_return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(0, 2);

    int aiChoiceNUM = distrib(gen);

    std::string aiChoice;
    std::string aiChoiceEmoji;
    std::string playerChoiceEmoji;
    std::string result;
    uint32_t resultColour;

    // this switch and the next two if statements really do not feel like a good solution.
    // but it works so let's just leave it.

    switch(aiChoiceNUM) {
        default:
            aiChoice = "rock";
            aiChoiceEmoji = dpp::unicode_emoji::rock;
            break;
        case 1:
            aiChoice = "paper";
            aiChoiceEmoji = dpp::unicode_emoji::newspaper;
            break;
        case 2:
            aiChoice = "scissors";
            aiChoiceEmoji = dpp::unicode_emoji::scissors;
            break;
    }

    if(event.custom_id == "rock") {
        playerChoiceEmoji = dpp::unicode_emoji::rock;
    } else if(event.custom_id == "paper") {
        playerChoiceEmoji = dpp::unicode_emoji::newspaper;
    } else {
        playerChoiceEmoji = dpp::unicode_emoji::scissors;
    }

    if (aiChoice == "rock") { // BUD-e chose Rock
        if (event.custom_id == "paper") {
            result = "You won!";
            resultColour = dpp::colours::green;
        } else if (event.custom_id == "scissors") {
            result = "I won!";
            resultColour = dpp::colours::red;
        }
    } else if (aiChoice == "paper") { // BUD-e chose Paper
        if (event.custom_id == "scissors") {
            result = "You Won!";
            resultColour = dpp::colours::green;
        } else if (event.custom_id == "rock") {
            result = "I Won!";
            resultColour = dpp::colours::red;
        }
    } else if (aiChoice == "scissors") { // BUD-e chose Scissors
        if (event.custom_id == "rock") {
            result = "You won!";
            resultColour = dpp::colours::green;
        } else if (event.custom_id == "paper") {
            result = "I won!";
            resultColour = dpp::colours::red;
        }
    } else { // Assume that player picked the same as BUD-e.
        result = "Draw!";
        resultColour = dpp::colours::yellow;
    }

    dpp::message msg(event.command.channel_id,
        embed_builder::basic_embed(
        resultColour, result,
        "I picked " + aiChoiceEmoji + " and you picked " + playerChoiceEmoji + "! Press the button below to play again!"
        )
    );

    component_builder::add_button_to_message(msg, component_data{"Play Again", "playagain", dpp::unicode_emoji::video_game});

    // Reply but edit previous message (need to reply or discord shows "interaction failed")
    event.reply(dpp::ir_update_message, msg);
}
