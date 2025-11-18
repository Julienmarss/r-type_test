#pragma once

#include "../core/System.hpp"

namespace rtype::engine {

class MovementSystem : public System {
public:
    MovementSystem();

    void update(float deltaTime, const std::vector<std::unique_ptr<Entity>>& entities) override;
};

}