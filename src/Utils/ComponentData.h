#include <string>

struct ComponentData {

    ComponentData(const std::string& _label, const std::string& _id, const std::string& _emoji) {
        this->label = _label;
        this->id = _id;
        this->emoji = _emoji;
    }

    std::string label;
    std::string id;
    std::string emoji;
};