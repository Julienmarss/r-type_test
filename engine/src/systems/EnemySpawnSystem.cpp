#include "engine/systems/EnemySpawnSystem.hpp"
#include "engine/core/Scene.hpp"
#include "engine/core/Entity.hpp"
#include "engine/physics/Transform.hpp"
#include "engine/physics/Velocity.hpp"
#include "engine/physics/Hitbox.hpp"
#include "engine/gameplay/Enemy.hpp"
#include "engine/gameplay/Health.hpp"
#include <random>

EnemySpawnSystem::EnemySpawnSystem(Scene& scene, float windowWidth, float windowHeight)
    : scene(scene), windowWidth(windowWidth), windowHeight(windowHeight),
      spawnTimer(0.f), spawnInterval(2.0f), rng(std::random_device{}())
{
}

void EnemySpawnSystem::update(float deltaTime, const std::vector<std::unique_ptr<Entity>>& entities)
{
    (void)entities;

    spawnTimer += deltaTime;
    if (spawnTimer < spawnInterval)
        return;

    spawnTimer = 0.f;
    spawnBasicEnemy();
}

void EnemySpawnSystem::spawnBasicEnemy()
{
    std::uniform_real_distribution<float> distY(50.f, windowHeight - 150.f);

    Entity& enemy = scene.createEntity();

    float startX = windowWidth + 50.f;
    float startY = distY(rng);

    auto transform = std::make_unique<Transform>(startX, startY);
    transform->scaleX = 0.6f;
    transform->scaleY = 0.6f;
    enemy.addComponent(std::move(transform));

    auto velocity = std::make_unique<Velocity>(-150.f, 0.f);
    enemy.addComponent(std::move(velocity));

    auto enemyComp = std::make_unique<Enemy>(EnemyType::Basic, 100);
    enemyComp->baseSpeedX = -150.f;
    enemyComp->baseSpeedY = 0.f;
    enemy.addComponent(std::move(enemyComp));

    enemy.addComponent(std::make_unique<Health>(50.f));

    enemy.addComponent(std::make_unique<Hitbox>(80.f, 60.f));
}
