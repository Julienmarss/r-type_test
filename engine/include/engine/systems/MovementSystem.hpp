#pragma once

#include "../ecs/System.hpp"
#include "../components/Transform.hpp"
#include "../components/Velocity.hpp"

namespace rtype::engine {

    class MovementSystem : public System {
    public:
        void update(Registry& registry, float deltaTime) override {
            for (auto [entity, transform, velocity] : registry.view<Transform, Velocity>()) {
                transform.x += velocity.x * deltaTime;
                transform.y += velocity.y * deltaTime;
            }
        }
    };

}