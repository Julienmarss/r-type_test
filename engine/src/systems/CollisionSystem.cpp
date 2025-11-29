#include "engine/systems/CollisionSystem.hpp"
#include "engine/core/Scene.hpp"
#include "engine/core/Entity.hpp"
#include "engine/physics/Transform.hpp"
#include "engine/physics/Hitbox.hpp"
#include "engine/gameplay/Projectile.hpp"
#include "engine/gameplay/Enemy.hpp"
#include "engine/gameplay/Health.hpp"

CollisionSystem::CollisionSystem(Scene& scene)
    : scene(scene)
{
}

void CollisionSystem::update(float deltaTime, const std::vector<std::unique_ptr<Entity>>& entities)
{
    (void)deltaTime;

    for (const auto& projEntity : entities) {
        auto* projectile = projEntity->getComponent<Projectile>();
        auto* projTransform = projEntity->getComponent<Transform>();
        auto* projHitbox = projEntity->getComponent<Hitbox>();

        if (!projectile || !projTransform || !projHitbox)
            continue;
        if (!projectile->isPlayerProjectile)
            continue;

        for (const auto& enemyEntity : entities) {
            auto* enemy = enemyEntity->getComponent<Enemy>();
            auto* health = enemyEntity->getComponent<Health>();
            auto* enemyTransform = enemyEntity->getComponent<Transform>();
            auto* enemyHitbox = enemyEntity->getComponent<Hitbox>();

            if (!enemy || !health || !enemyTransform || !enemyHitbox)
                continue;

            if (!intersects(*projEntity, *enemyEntity))
                continue;

            if (!health->invincible) {
                health->currentHp -= projectile->damage;
            }

            if (!projectile->piercing) {
                scene.markEntityForDestruction(projEntity->getID());
            }

            if (health->isDead()) {
                scene.markEntityForDestruction(enemyEntity->getID());
            }
        }
    }
}

bool CollisionSystem::intersects(const Entity& a, const Entity& b) const
{
    auto* ta = const_cast<Entity&>(a).getComponent<Transform>();
    auto* ha = const_cast<Entity&>(a).getComponent<Hitbox>();
    auto* tb = const_cast<Entity&>(b).getComponent<Transform>();
    auto* hb = const_cast<Entity&>(b).getComponent<Hitbox>();

    if (!ta || !ha || !tb || !hb)
        return false;

    float leftA   = ta->x;
    float rightA  = ta->x + ha->width;
    float topA    = ta->y;
    float bottomA = ta->y + ha->height;

    float leftB   = tb->x;
    float rightB  = tb->x + hb->width;
    float topB    = tb->y;
    float bottomB = tb->y + hb->height;

    return !(rightA < leftB ||
             leftA > rightB ||
             bottomA < topB ||
             topA > bottomB);
}
