#pragma once

#include <dpp/dpp.h>
#include <random>
#include "../Utils/EmbedBuilder.h"
#include "../Utils/ComponentBuilder.h"

class RPSListener {

public:

    static void OnButtonClick(const dpp::button_click_t& event) {

        // Handle playing again.
        if(event.custom_id == "playagain") {

            dpp::message msg(event.command.channel_id,
                             EmbedBuilder::BasicEmbed(dpp::colours::aqua,
                            "Rock, Paper Scissors!",
                            "Let's play rock, paper, scissors! You pick and I'll pick!")
            );

            // this is now nice :)

            ComponentBuilder::AddButtonToMessage(msg, {ComponentData("Rock", "rock", u8"🪨"),
                                                       ComponentData("Paper", "paper", u8"📰"),
                                                       ComponentData("Scissors", "scissors", u8"✂️")}
            );

            event.reply(dpp::ir_update_message, msg);

            return;
        }

        // If the event wasn't rock, nor paper, nor scissors, then just return.
        // This handler is not made for anything else, and we've already handled playing again (if that was the case).
        if(event.custom_id != "rock" && event.custom_id != "paper" && event.custom_id != "scissors")
            return;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distrib(0, 99);

        // This will return either 0, 1 or 2. Going from 0-99 means we have more to play with as
        // 0-2 was yielding results that did not feel random.
        int aiChoiceNUM = (distrib(gen)/33) - 1;

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
                aiChoiceEmoji = u8"🪨";
                break;
            case 1:
                aiChoice = "paper";
                aiChoiceEmoji = u8"📰";
                break;
            case 2:
                aiChoice = "scissors";
                aiChoiceEmoji = u8"✂️";
                break;
        }

        if(event.custom_id == "rock") {
            playerChoiceEmoji = u8"🪨";
        } else if(event.custom_id == "paper") {
            playerChoiceEmoji = u8"📰";
        } else {
            playerChoiceEmoji = u8"✂️";
        }

        // if BUD-e picked rock and player picked paper.
        if(aiChoice == "rock" && event.custom_id == "paper") {
            result = "You won!";
            resultColour = dpp::colours::green;
        } else if(aiChoice == "rock" && event.custom_id == "scissors") {
            result = "I won!";
            resultColour = dpp::colours::red;
        } else if (aiChoice == "paper" && event.custom_id == "scissors") {
            result = "You Won!";
            resultColour = dpp::colours::green;
        } else if (aiChoice == "paper" && event.custom_id == "rock") {
            result = "I Won!";
            resultColour = dpp::colours::red;
        } else if (aiChoice == "scissors" && event.custom_id == "rock") {
            result = "You won!";
            resultColour = dpp::colours::green;
        } else if (aiChoice == "scissors" && event.custom_id == "paper") {
            result = "I won!";
            resultColour = dpp::colours::red;
        } else { // Assume that player picked the same as BUD-e.
            result = "Draw!";
            resultColour = dpp::colours::yellow;
        }

        dpp::message msg(event.command.channel_id,
                         EmbedBuilder::BasicEmbed(resultColour,result,
                      "I picked " + aiChoiceEmoji + " and you picked " + playerChoiceEmoji + "! Press the button below to play again!")
        );

        ComponentBuilder::AddButtonToMessage(msg, ComponentData("Play Again", "playagain", u8"🎮"));

        // Reply but edit previous message (need to reply or discord shows "interaction failed")
        event.reply(dpp::ir_update_message, msg);
    }

};