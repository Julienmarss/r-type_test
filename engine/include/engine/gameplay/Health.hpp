#pragma once
#include "engine/core/Component.hpp"

class Health : public Component {
public:
    Health();
    explicit Health(float maxHp);

    float maxHp;
    float currentHp;
    bool invincible;

    bool isDead() const { return currentHp <= 0.f; }
};
