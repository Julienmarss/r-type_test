#include "engine/systems/AnimationSystem.hpp"
#include "engine/core/Entity.hpp"
#include "engine/graphics/Animation.hpp"
#include "engine/graphics/Sprite.hpp"
#include <SFML/Graphics/Rect.hpp>

AnimationSystem::AnimationSystem() = default;

void AnimationSystem::update(float deltaTime, const std::vector<std::unique_ptr<Entity>>& entities) {
    for (const auto& entity : entities) {
        auto* animation = entity->getComponent<Animation>();
        auto* sprite = entity->getComponent<Sprite>();
        
        if (!animation || !sprite || animation->frameCount == 0) continue;
        
        animation->elapsedTime += deltaTime;
        
        if (animation->elapsedTime >= animation->frameTime) {
            animation->elapsedTime = 0.f;
            animation->currentFrame++;
            
            if (animation->currentFrame >= animation->frameCount) {
                if (animation->loop) {
                    animation->currentFrame = 0;
                } else {
                    animation->currentFrame = animation->frameCount - 1;
                }
            }
            
            const AnimationFrame* frame = animation->getCurrentFrame();
            if (frame) {
                sprite->getSprite().setTextureRect(
                    sf::IntRect(frame->x, frame->y, frame->width, frame->height)
                );
            }
        }
    }
}