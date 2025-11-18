#include "engine/systems/MovementSystem.hpp"
#include "engine/core/Entity.hpp"
#include "engine/physics/Transform.hpp"
#include "engine/physics/Velocity.hpp"

namespace rtype::engine {

MovementSystem::MovementSystem() {
}

void MovementSystem::update(float deltaTime, const std::vector<std::unique_ptr<Entity>>& entities) {
    for (const std::unique_ptr<Entity>& entity : entities) {
        Transform* transform = static_cast<Transform*>(entity->getComponent("Transform"));
        Velocity* velocity = static_cast<Velocity*>(entity->getComponent("Velocity"));
        
        if (transform && velocity) {
            transform->x += velocity->x * deltaTime;
            transform->y += velocity->y * deltaTime;
        }
    }
}

}