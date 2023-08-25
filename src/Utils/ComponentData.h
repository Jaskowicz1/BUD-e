#include <string>

struct ComponentData {

    ComponentData(std::string_view _label, std::string_view _id, std::string_view _emoji)
    : label(_label), id(_id), emoji(_emoji) {};

    std::string label;
    std::string id;
    std::string emoji;
};