#pragma once
#include "engine/core/System.hpp"

class EnemyVisualSystem : public System {
public:
    EnemyVisualSystem() = default;

    void update(float deltaTime, const std::vector<std::unique_ptr<Entity>>& entities) override;
};
