#include "engine/systems/EnemyBehaviorSystem.hpp"
#include "engine/core/Entity.hpp"
#include "engine/physics/Transform.hpp"
#include "engine/physics/Velocity.hpp"
#include "engine/gameplay/Enemy.hpp"
#include <cmath>

EnemyBehaviorSystem::EnemyBehaviorSystem() = default;

void EnemyBehaviorSystem::update(float deltaTime, const std::vector<std::unique_ptr<Entity>>& entities)
{
    static float globalTime = 0.f;
    globalTime += deltaTime;

    for (const auto& entity : entities) {
        auto* enemy = entity->getComponent<Enemy>();
        auto* velocity = entity->getComponent<Velocity>();

        if (!enemy || !velocity)
            continue;

        switch (enemy->type) {
        case EnemyType::Basic:
            // mouvement tout droit (géré principalement par MovementSystem via Velocity)
            velocity->x = enemy->baseSpeedX;
            velocity->y = enemy->baseSpeedY;
            break;
        case EnemyType::Fast:
            velocity->x = enemy->baseSpeedX * 1.8f;
            velocity->y = std::sin(globalTime * 4.f) * 120.f;
            break;
        case EnemyType::Tank:
            velocity->x = enemy->baseSpeedX * 0.5f;
            velocity->y = 0.f;
            break;
        }
    }
}
