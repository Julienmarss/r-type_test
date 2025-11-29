#pragma once
#include "engine/core/System.hpp"
#include <random>

class Scene;

class EnemySpawnSystem : public System {
public:
    EnemySpawnSystem(Scene& scene, float windowWidth, float windowHeight);

    void update(float deltaTime, const std::vector<std::unique_ptr<Entity>>& entities) override;

private:
    void spawnBasicEnemy();

    Scene& scene;
    float windowWidth;
    float windowHeight;

    float spawnTimer;
    float spawnInterval;

    std::mt19937 rng;
};
