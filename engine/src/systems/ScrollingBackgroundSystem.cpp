#include "engine/systems/ScrollingBackgroundSystem.hpp"
#include "engine/core/Entity.hpp"
#include "engine/physics/Transform.hpp"
#include "engine/physics/Velocity.hpp"

ScrollingBackgroundSystem::ScrollingBackgroundSystem(float windowWidth) 
    : windowWidth(windowWidth) {
}

void ScrollingBackgroundSystem::update(float deltaTime, const std::vector<std::unique_ptr<Entity>>& entities) {
    (void)deltaTime;
    
    for (const auto& entity : entities) {
        auto* transform = entity->getComponent<Transform>();
        auto* velocity = entity->getComponent<Velocity>();
        
        if (!transform || !velocity) continue;
        
        if (transform->x + windowWidth <= 0.0f) {
            transform->x += windowWidth * 2.0f;
        }
    }
}