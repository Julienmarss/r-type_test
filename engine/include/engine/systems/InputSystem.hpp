#pragma once
#include "engine/core/System.hpp"

class Renderer;

class InputSystem : public System {
public:
    explicit InputSystem(Renderer& renderer);
    
    void update(float deltaTime, const std::vector<std::unique_ptr<Entity>>& entities) override;

private:
    Renderer& renderer;
};