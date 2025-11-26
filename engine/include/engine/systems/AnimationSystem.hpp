#pragma once
#include "engine/core/System.hpp"

class AnimationSystem : public System {
public:
    AnimationSystem();
    
    void update(float deltaTime, const std::vector<std::unique_ptr<Entity>>& entities) override;
};