﻿#pragma once

#include <dpp/dpp.h>

class embed_builder {

public:

	static inline dpp::embed basic_embed(const uint32_t textColour, const std::string& title, const std::string& description) {
		return dpp::embed()
		.set_color(textColour)
		.set_title(title)
		.set_description(description);
	}

	static inline dpp::embed basic_embed_with_timestamp(const uint32_t textColour, const std::string& title, const std::string& description) {
		return dpp::embed()
			.set_color(textColour)
			.set_title(title)
			.set_description(description)
			.set_timestamp(time(0));
	}

	static inline dpp::embed basic_embed_with_footer(const uint32_t textColour, const std::string& title, const std::string& description,
	const dpp::embed_footer& footer) {
		return dpp::embed()
			.set_color(textColour)
			.set_title(title)
			.set_description(description)
			.set_footer(footer);
	}

	static inline dpp::embed full_embed(const uint32_t textColour, const std::string& title, const std::string& description, const std::string& url,
	const dpp::embed_author& author, const std::vector<dpp::embed_field>& fields, const std::string& thumbnail,
	const std::string& imageURL, const dpp::embed_footer& footer, const time_t& timestamp) {
		dpp::embed currentEmbed = dpp::embed()
			.set_color(textColour)
			.set_title(title)
			.set_url(url)
			.set_author(author.name, author.url, author.icon_url)
			.set_description(description)
			.set_thumbnail(thumbnail)
			.set_image(imageURL)
			.set_footer(footer)
			.set_timestamp(timestamp);

		for(const dpp::embed_field& field : fields) {
			currentEmbed.add_field(field.name, field.value, field.is_inline);
		}

		return currentEmbed;
	}

	static inline void add_fields_to_embed(dpp::embed& embed, const std::vector<dpp::embed_field>& fields) {
		for(const dpp::embed_field& field : fields) {
			embed.add_field(field.name, field.value, field.is_inline);
		}
	}

	static inline void add_field_to_embed(dpp::embed& embed, const dpp::embed_field& field) {
		embed.add_field(field.name, field.value, field.is_inline);
	}
};