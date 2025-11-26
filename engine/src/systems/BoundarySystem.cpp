#include "engine/systems/BoundarySystem.hpp"
#include "engine/core/Entity.hpp"
#include "engine/physics/Transform.hpp"
#include "engine/gameplay/Controllable.hpp"

BoundarySystem::BoundarySystem(float minX, float maxX, float minY, float maxY)
    : minX(minX), maxX(maxX), minY(minY), maxY(maxY) {
}

void BoundarySystem::update(float deltaTime, const std::vector<std::unique_ptr<Entity>>& entities) {
    (void)deltaTime;
    
    for (const auto& entity : entities) {
        auto* transform = entity->getComponent<Transform>();
        auto* controllable = entity->getComponent<Controllable>();
        
        if (!transform || !controllable) continue;
        
        if (transform->x < minX) transform->x = minX;
        if (transform->x > maxX) transform->x = maxX;
        if (transform->y < minY) transform->y = minY;
        if (transform->y > maxY) transform->y = maxY;
    }
}