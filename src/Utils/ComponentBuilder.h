#pragma once

#include <dpp/dpp.h>

class ComponentBuilder {

public:

    static void AddButtonToMessage(dpp::message& message, const std::string& label, const std::string& id, const std::string& emoji = "") {

        dpp::component component;

        component.add_component(dpp::component().
            set_label(label).
            set_type(dpp::cot_button).
            set_emoji(emoji).
            set_style(dpp::cos_primary).
            set_id(id)
        );

        message.add_component(component);

        /* This is how it's usually done (except it'd be .add_component(dpp:component().add_component());
        if(message.components.empty()) {
            message.add_component(component);
        } else {
            message.components[0].add_component(component);
        }
         */
    }
};