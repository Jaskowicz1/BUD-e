#pragma once

#include <dpp/dpp.h>
#include <random>
#include "../EmbedBuilder.h"

class RPSListener {

public:

    static void OnButtonClick(const dpp::button_click_t& event) {

        // Handle playing again.
        if(event.custom_id != "playagain") {
            dpp::message msg = event.command.get_context_message();
            msg.suppress_embeds();
            msg.add_embed(
            EmbedBuilder::BasicEmbed(dpp::colours::aqua,
             "Rock, Paper Scissors!",
             "Let's play rock, paper, scissors! You pick and I'll pick!"));

            // I'm really considering turning this into a function or something because it looks ugly sitting here...
            msg.add_component ( // Add component to message
                dpp::component() // comp class
                    .add_component(
                        dpp::component().set_label("Rock").
                            set_type(dpp::cot_button).
                            set_emoji(u8"🪨").
                            set_style(dpp::cos_primary).
                            set_id("rock")
                    )
                    .add_component(
                        dpp::component().set_label("Paper").
                            set_type(dpp::cot_button).
                            set_emoji(u8"📰").
                            set_style(dpp::cos_primary).
                            set_id("paper")
                    )
                    .add_component(
                        dpp::component().set_label("Scissors").
                            set_type(dpp::cot_button).
                            set_emoji(u8"✂️").
                            set_style(dpp::cos_primary).
                            set_id("scissors")
                    )
            );

            BUDe::botRef->message_edit(msg);

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
        std::string result;

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

        if(aiChoice == event.custom_id) {
            result = "Draw!";

            dpp::message msg = event.command.get_context_message();

            // remove all embeds.
            msg.suppress_embeds();
            msg.add_embed(EmbedBuilder::BasicEmbed(dpp::colours::aqua,result,
                                                   "I picked " + aiChoiceEmoji + "! Press the button below to play again!"));

            msg.add_component(
                dpp::component()
                    .add_component(
                            dpp::component().set_label("Play Again!").
                                    set_type(dpp::cot_button).
                                    set_emoji(u8"🎮").
                                    set_style(dpp::cos_primary).
                                    set_id("playagain")
                    )
            );

            BUDe::botRef->message_edit(msg);
            return;
        }

        // if BUD-e picked rock and player picked paper.
        if(aiChoice == "rock" && event.custom_id == "paper")
            result = "You won!";
        else if(aiChoice == "rock" && event.custom_id == "scissors")
            result = "I won!";
        else if(aiChoice == "paper" && event.custom_id == "rock")
            result = "You Won!";
        else if(aiChoice == "paper" && event.custom_id == "scissors")
            result = "I Won!";
        else if(aiChoice == "scissors" && event.custom_id == "rock")
            result = "You won!";
        else if(aiChoice == "scissors" && event.custom_id == "paper")
            result = "I won!";

        dpp::message msg = event.command.get_context_message();

        // remove all embeds.
        msg.suppress_embeds();
        msg.add_embed(EmbedBuilder::BasicEmbed(dpp::colours::aqua,result,
                                               "I picked " + aiChoiceEmoji + "! Pick a choice to play again!"));

        // I'm really considering turning this into a function or something because it looks ugly sitting here...
        msg.add_component(
            dpp::component()
                .add_component(
                    dpp::component().set_label("Play Again").
                        set_type(dpp::cot_button).
                        set_emoji(u8"🎮").
                        set_style(dpp::cos_primary).
                        set_id("rock")
                )
        );

        // Edit the original message to say our new message.
        BUDe::botRef->message_edit(msg);
    }

};