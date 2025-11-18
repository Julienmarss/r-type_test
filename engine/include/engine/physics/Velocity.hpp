#pragma once

#include "../core/Component.hpp"

namespace rtype::engine {

class Velocity : public Component {
public:
    Velocity();
    Velocity(float vx, float vy);

    float x;
    float y;
};

}