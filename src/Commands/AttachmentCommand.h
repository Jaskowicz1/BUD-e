#pragma once

#include "Core/Command.h"
#include "../Utils/EmbedBuilder.h"
#include "../BUDe.h"

class AttachmentCommand : public Command {

public:

    AttachmentCommand() : Command("attachment", "Send a testing attachment.") {};

    void Execute(const dpp::slashcommand_t& event) override {
        // request an image
        BUDe::botRef->request("https://dpp.dev/DPP-Logo.png", dpp::m_get, [event, channel_id = event.command.channel_id](const dpp::http_request_completion_t & httpRequestCompletion) {

            // create a message
            dpp::message msg(channel_id, "This is my new attachment:");

            // attach the image on success
            if (httpRequestCompletion.status == 200) {
                msg.add_file("logo.png", httpRequestCompletion.body);
            }

            // send the message
            event.reply(msg);
        });
    };

    bool Enabled() override {
        return true;
    }

    bool Private() override {
        return true;
    }

};