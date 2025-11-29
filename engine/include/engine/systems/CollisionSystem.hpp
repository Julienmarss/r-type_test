#pragma once
#include "engine/core/System.hpp"

class Scene;

class CollisionSystem : public System {
public:
    explicit CollisionSystem(Scene& scene);

    void update(float deltaTime, const std::vector<std::unique_ptr<Entity>>& entities) override;

private:
    bool intersects(const Entity& a, const Entity& b) const;

    Scene& scene;
};
