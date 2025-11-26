#include "engine/systems/RenderSystem.hpp"
#include "engine/core/Entity.hpp"
#include "engine/graphics/Renderer.hpp"
#include "engine/graphics/Sprite.hpp"
#include "engine/physics/Transform.hpp"

RenderSystem::RenderSystem() = default;

void RenderSystem::update(float, const std::vector<std::unique_ptr<Entity>>&) {
}

void RenderSystem::render(Renderer& renderer, const std::vector<std::unique_ptr<Entity>>& entities) {
    for (const auto& entity : entities) {
        auto* sprite = entity->getComponent<Sprite>();
        auto* transform = entity->getComponent<Transform>();
        
        if (sprite && transform) {
            sprite->setPosition(transform->x, transform->y);
            sprite->setScale(transform->scaleX, transform->scaleY);
            renderer.getWindow().draw(sprite->getSprite());
        }
    }
}