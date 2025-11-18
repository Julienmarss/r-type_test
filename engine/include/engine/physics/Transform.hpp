#pragma once

#include "../core/Component.hpp"

namespace rtype::engine {

class Transform : public Component {
public:
    Transform();
    Transform(float x, float y);

    float x;
    float y;
    float rotation;
    float scaleX;
    float scaleY;
};

}