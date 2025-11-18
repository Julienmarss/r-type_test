#include "engine/core/Entity.hpp"

namespace rtype::engine {

Entity::Entity(EntityID id) : id(id) {
}

EntityID Entity::getID() const {
    return id;
}

void Entity::addComponent(const std::string& type, std::unique_ptr<Component> component) {
    components[type] = std::move(component);
}

Component* Entity::getComponent(const std::string& type) {
    auto it = components.find(type);
    if (it != components.end()) {
        return it->second.get();
    }
    return nullptr;
}

bool Entity::hasComponent(const std::string& type) const {
    return components.find(type) != components.end();
}

}