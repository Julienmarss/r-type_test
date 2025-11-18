#include "engine/systems/RenderSystem.hpp"
#include "engine/core/Entity.hpp"
#include "engine/graphics/Renderer.hpp"
#include "engine/graphics/Sprite.hpp"
#include "engine/physics/Transform.hpp"

namespace rtype::engine {

RenderSystem::RenderSystem() {
}

void RenderSystem::update(float, const std::vector<std::unique_ptr<Entity>>&) {
}

void RenderSystem::render(Renderer& renderer, const std::vector<std::unique_ptr<Entity>>& entities) {
    for (const std::unique_ptr<Entity>& entity : entities) {
        Sprite* sprite = static_cast<Sprite*>(entity->getComponent("Sprite"));
        Transform* transform = static_cast<Transform*>(entity->getComponent("Transform"));
        
        if (sprite && transform) {
            sprite->setPosition(transform->x, transform->y);
            sprite->setScale(transform->scaleX, transform->scaleY);
            renderer.getWindow().draw(sprite->getSprite());
        }
    }
}

}