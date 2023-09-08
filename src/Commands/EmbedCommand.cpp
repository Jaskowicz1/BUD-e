//
// Created by archie on 02/09/23.
//
#include "EmbedCommand.h"

void EmbedCommand::Execute(const dpp::slashcommand_t &event) {
    dpp::embed embed = dpp::embed().
        set_color(dpp::colors::sti_blue).
        set_title("Some name").
        set_url("https://dpp.dev/").
        set_author("Some name", "https://dpp.dev/", "https://dpp.dev/DPP-Logo.png").
        set_description("Some description here").
        set_thumbnail("https://dpp.dev/DPP-Logo.png").
        add_field(
        "Regular field title",
        "Some value here"
    ).
        add_field(
        "Inline field title",
        "Some value here",
        true
    ).
        add_field(
        "Inline field title",
        "Some value here",
        true
    ).
        set_image("https://dpp.dev/DPP-Logo.png").
        set_footer(dpp::embed_footer().set_text("Some footer text here").set_icon("https://dpp.dev/DPP-Logo.png")).
        set_timestamp(time(0));

    /* Create a message with the content as our new embed. */
    dpp::message msg(event.command.channel_id, embed);

    /* Reply to the user with the message, containing our embed. */
    event.reply(msg);
}

