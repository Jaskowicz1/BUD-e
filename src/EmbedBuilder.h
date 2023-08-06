#pragma once
#include <dpp/colors.h>
#include <list>
#include "dpp/message.h"

class EmbedBuilder
{
public:

    static inline dpp::embed BasicEmbed(const uint32_t textColour, const std::string& title, const std::string& description)
    {
        return dpp::embed().
                set_color(textColour).
                set_title(title).
                set_description(description);
    }

    static inline dpp::embed BasicEmbedWithTimestamp(const uint32_t textColour, const std::string& title, const std::string& description)
    {
        return dpp::embed().
                set_color(textColour).
                set_title(title).
                set_description(description).
                set_timestamp(time(0));
    }

    static inline dpp::embed FullEmbed(const uint32_t textColour, const std::string& title, const std::string& description, const std::string& url,
        const dpp::embed_author& author, const std::list<dpp::embed_field>& fields, const std::string& thumbnail, const std::string& imageURL, 
        const dpp::embed_footer& footer, const time_t& timestamp)
    {
        dpp::embed currentEmbed = dpp::embed().
                set_color(textColour).
                set_title(title).
                set_url(url).
                set_author(author.name, author.url, author.icon_url).
                set_description(description).
                set_thumbnail(thumbnail).
                set_image(imageURL).
                set_footer(footer).
                set_timestamp(timestamp);

        for(dpp::embed_field field : fields)
        {
            currentEmbed.add_field(field.name, field.value, field.is_inline);
        }

        return currentEmbed;
    }
    
};