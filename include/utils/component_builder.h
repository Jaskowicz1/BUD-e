#pragma once

#include <dpp/dpp.h>
#include "component_data.h"

class component_builder {

public:

	inline static void add_button_to_message(dpp::message& message, const component_data& data) {
		dpp::component component;

		component.set_label(data.label).
		set_type(dpp::cot_button).
		set_emoji(data.emoji).
		set_style(dpp::cos_primary).
		set_id(data.id);

		message.components.clear();
		message.add_component(dpp::component().add_component(component));
	}

	inline static void add_buttons_to_message(dpp::message& message, const std::vector<component_data>& dataValues) {
		dpp::component component;

		for(const component_data& data : dataValues) {
			component.add_component(dpp::component().
			set_label(data.label).
			set_type(dpp::cot_button).
			set_emoji(data.emoji).
			set_style(dpp::cos_primary).
			set_id(data.id)
			);
		}

		message.components.clear();
		message.add_component(component);
	}
};
