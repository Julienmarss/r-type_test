#pragma once
#include "engine/core/Component.hpp"

class Hitbox : public Component {
public:
    Hitbox();
    Hitbox(float width, float height);

    float width;
    float height;
};
