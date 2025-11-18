#pragma once

#include "Component.hpp"
#include <cstdint>
#include <unordered_map>
#include <memory>
#include <string>

namespace rtype::engine {

using EntityID = uint32_t;

class Entity {
public:
    explicit Entity(EntityID id);

    EntityID getID() const;

    void addComponent(const std::string& type, std::unique_ptr<Component> component);
    Component* getComponent(const std::string& type);
    bool hasComponent(const std::string& type) const;

private:
    EntityID id;
    std::unordered_map<std::string, std::unique_ptr<Component>> components;
};

}