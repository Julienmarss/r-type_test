#pragma once
#include "engine/core/Component.hpp"

class Controllable : public Component {
public:
    Controllable();
    explicit Controllable(float speed);

    float speed;
    bool canShoot;
    float shootCooldown; //le cooldown va diminuer à chaque level up (futur feature)
    float currentCooldown;
};