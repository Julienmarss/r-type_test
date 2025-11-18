#pragma once

#include "../core/System.hpp"

namespace rtype::engine {

class RenderSystem : public System {
public:
    RenderSystem();

    void update(float deltaTime, const std::vector<std::unique_ptr<Entity>>& entities) override;
    void render(Renderer& renderer, const std::vector<std::unique_ptr<Entity>>& entities) override;
};

}