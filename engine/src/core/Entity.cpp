#include "engine/core/Entity.hpp"
#include "engine/core/Component.hpp"

Entity::Entity(EntityID id) : id(id) {
}

EntityID Entity::getID() const {
    return id;
}