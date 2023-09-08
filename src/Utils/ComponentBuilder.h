#pragma once

#include <dpp/dpp.h>
#include "ComponentData.h"

class ComponentBuilder {

public:

    inline static void AddButtonToMessage(dpp::message& message, const ComponentData& data) {

        dpp::component component;

        component.set_label(data.label).
        set_type(dpp::cot_button).
        set_emoji(data.emoji).
        set_style(dpp::cos_primary).
        set_id(data.id);

        message.components.clear();
        message.add_component(dpp::component().add_component(component));
    }

    inline static void AddButtonsToMessage(dpp::message& message, const std::vector<ComponentData>& dataValues) {

        dpp::component component;

        for(const ComponentData& data : dataValues) {
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