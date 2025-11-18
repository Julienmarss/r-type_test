#pragma once

namespace rtype::engine {

    struct Transform {
        float x = 0.f;
        float y = 0.f;
        float rotation = 0.f;
        float scaleX = 1.f;
        float scaleY = 1.f;

        Transform() = default;
        Transform(float x, float y) : x(x), y(y) {}
    };

}
