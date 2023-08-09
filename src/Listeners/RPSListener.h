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
            ComponentBuilder::AddButtonToMessage(msg, "Rock", "rock", u8"🪨");
            ComponentBuilder::AddButtonToMessage(msg, "Paper", "paper", u8"📰");
            ComponentBuilder::AddButtonToMessage(msg, "Scissors", "scissors", u8"✂️");

            event.reply(dpp::ir_update_message, msg);

            return;
        }

        if(event.custom_id != "rock" && event.custom_id != "paper" && event.custom_id != "scissors")
            return;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 2);

        int aiChoiceNUM = distrib(gen);

        std::string aiChoice;
        std::string aiChoiceEmoji;
        std::string playerChoiceEmoji;
        std::string result;

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
        if(aiChoice == "rock" && event.custom_id == "paper")
            result = "You won!";
        else if(aiChoice == "rock" && event.custom_id == "scissors") // so on...
            result = "I won!";
        else if(aiChoice == "paper" && event.custom_id == "rock")
            result = "You Won!";
        else if(aiChoice == "paper" && event.custom_id == "scissors")
            result = "I Won!";
        else if(aiChoice == "scissors" && event.custom_id == "rock")
            result = "You won!";
        else if(aiChoice == "scissors" && event.custom_id == "paper")
            result = "I won!";
        else // Assume that player picked the same as BUD-e.
            result = "Draw!";

        dpp::message msg(event.command.channel_id,
                         EmbedBuilder::BasicEmbed(dpp::colours::aqua,result,
                      "I picked " + aiChoiceEmoji + " and you picked " + playerChoiceEmoji + "! Press the button below to play again!")
        );

        ComponentBuilder::AddButtonToMessage(msg, "Play Again", "playagain", u8"🎮");

        event.reply(dpp::ir_update_message, msg);
    }

};