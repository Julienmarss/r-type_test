#pragma once
#include "engine/core/System.hpp"

class Scene;

class ShootingSystem : public System {
public:
    explicit ShootingSystem(Scene& scene, float windowWidth);
    
    void update(float deltaTime, const std::vector<std::unique_ptr<Entity>>& entities) override;

private:
    void createNormalShot(float x, float y);
    void createChargedShot(float x, float y);
    void cleanupOffscreenProjectiles(const std::vector<std::unique_ptr<Entity>>& entities);
    
    Scene& scene;
    float windowWidth;
    float chargeTime;
    bool wasSpacePressed;
};