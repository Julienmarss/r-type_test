#include "engine/systems/EnemyVisualSystem.hpp"
#include "engine/core/Entity.hpp"
#include "engine/gameplay/Enemy.hpp"
#include "engine/graphics/Sprite.hpp"
#include "engine/physics/Transform.hpp"

void EnemyVisualSystem::update(float, const std::vector<std::unique_ptr<Entity>>& entities)
{
    for (const auto& entity : entities) {
        auto* enemy = entity->getComponent<Enemy>();
        auto* transform = entity->getComponent<Transform>();
        if (!enemy || !transform)
            continue;

        // Si l'entité a déjà un sprite, ne rien faire
        if (entity->hasComponent<Sprite>())
            continue;

        auto sprite = std::make_unique<Sprite>();

        switch (enemy->type) {
        case EnemyType::Basic:
        default:
            sprite->loadTexture("assets/sprites/enemy_basic.png");
            break;
        }

        entity->addComponent(std::move(sprite));
    }
}
