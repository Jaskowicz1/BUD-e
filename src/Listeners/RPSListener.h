#pragma once

#include <dpp/dpp.h>
#include <random>
#include "../EmbedBuilder.h"

class RPSListener {

public:

    static void OnButtonClick(const dpp::button_click_t& event) {
        if(event.custom_id != "rock" && event.custom_id != "paper" && event.custom_id != "scissors")
            return;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 2);

        int aiChoiceNUM = distrib(gen);

        std::string aiChoice;
        std::string aiChoiceEmoji;
        std::string result;

        dpp::embed_footer footer;
        footer.set_text("Invoked by: " + event.command.usr.username);

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

            // what even happened to the damn indentation????????????????
            event.edit_original_response(
                    dpp::message(event.command.channel_id,
                      EmbedBuilder::BasicEmbedWithFooter(dpp::colours::aqua,result,
                      "I picked " + aiChoiceEmoji + "! Pick a choice to play again!", footer))
                      .add_component(
                              dpp::component()
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
                     )
            );
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

        // I don't even want to talk about how ugly this looks. I am going to have nightmares about this.
        event.edit_original_response(
                dpp::message(event.command.channel_id,
                             EmbedBuilder::BasicEmbedWithFooter(dpp::colours::aqua,result,
                                                                "I picked " + aiChoiceEmoji + "! Pick a choice to play again!", footer))
                        .add_component(
                                dpp::component()
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
                        )
        );
    }

};