#pragma once
#include "engine/core/System.hpp"

class EnemyBehaviorSystem : public System {
public:
    EnemyBehaviorSystem();

    void update(float deltaTime, const std::vector<std::unique_ptr<Entity>>& entities) override;
};
