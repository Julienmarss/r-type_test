#pragma once

namespace rtype::engine {

    struct Velocity {
        float x = 0.f;
        float y = 0.f;

        Velocity() = default;
        Velocity(float x, float y) : x(x), y(y) {}
    };

}
