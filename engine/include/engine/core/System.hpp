#pragma once
#include <vector>
#include <memory>

class Entity;
class Renderer;

class System {
public:
    virtual ~System() = default;

    virtual void update(float deltaTime, const std::vector<std::unique_ptr<Entity>>& entities) = 0;
    virtual void render(Renderer& renderer, const std::vector<std::unique_ptr<Entity>>& entities);
};