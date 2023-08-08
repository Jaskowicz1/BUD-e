#pragma once

#include <dpp/dpp.h>
#include <random>

class RPSListener {

public:

    static void OnButtonClick(const dpp::button_click_t& event) {
        if(event.custom_id != "rock" && event.custom_id != "paper" && event.custom_id != "scissors")
            return;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 2);

        std::string aiChoice;
        std::string result;

        switch(distrib(gen)) {
            case 0:
                aiChoice = "rock";
                break;
            case 1:
                aiChoice = "paper";
                break;
            case 2:
                aiChoice = "scissors";
                break;
            default:
                aiChoice = "rock";
                break;
        }

        if(aiChoice == event.custom_id) {
            result = "Draw!";

            event.reply(dpp::message(result).set_flags(dpp::m_ephemeral));
            return;
        }

        // if BUD-e picked rock and player picked paper.
        if(aiChoice == "rock" && event.custom_id == "paper")
            result = "You won!";
        else if(aiChoice == "rock" && event.custom_id == "scissors")
            result = "I won!";
        else if(aiChoice == "paper" && event.custom_id == "scissors")
            result = "You Won!";
        else if(aiChoice == "paper" && event.custom_id == "rock")
            result = "I won!";
        else if(aiChoice == "scissors" && event.custom_id == "paper")
            result = "You won!";
        else if(aiChoice == "scissors" && event.custom_id == "rock")
            result = "I won!";


        event.reply(dpp::message(result).set_flags(dpp::m_ephemeral));
    }

};