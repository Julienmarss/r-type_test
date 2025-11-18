#pragma once

#include "Registry.hpp"

namespace rtype::engine {

    class System {
    public:
        virtual ~System() = default;
        virtual void update(Registry& registry, float deltaTime) = 0;
    };

}
