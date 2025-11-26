#include "engine/systems/MovementSystem.hpp"
#include "engine/core/Entity.hpp"
#include "engine/physics/Transform.hpp"
#include "engine/physics/Velocity.hpp"

MovementSystem::MovementSystem() = default;

void MovementSystem::update(float deltaTime, const std::vector<std::unique_ptr<Entity>>& entities) {
    for (const auto& entity : entities) {
        auto* transform = entity->getComponent<Transform>();
        auto* velocity = entity->getComponent<Velocity>();
        
        if (transform && velocity) {
            transform->x += velocity->x * deltaTime;
            transform->y += velocity->y * deltaTime;
        }
    }
}