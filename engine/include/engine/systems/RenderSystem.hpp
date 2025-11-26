#pragma once
#include "engine/core/System.hpp"

class RenderSystem : public System {
public:
    RenderSystem();
    
    void update(float deltaTime, const std::vector<std::unique_ptr<Entity>>& entities) override;
    void render(Renderer& renderer, const std::vector<std::unique_ptr<Entity>>& entities) override;
};