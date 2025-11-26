#pragma once
#include "engine/core/Component.hpp"

class Velocity : public Component {
public:
    Velocity();
    Velocity(float vx, float vy);

    float x;
    float y;
};