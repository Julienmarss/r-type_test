#pragma once
#include "engine/core/Component.hpp"
#include <cstdint>

enum class EnemyType : std::uint8_t {
    Basic = 0,
    Fast,
    Tank
};

class Enemy : public Component {
public:
    Enemy();
    Enemy(EnemyType type, int scoreValue);

    EnemyType type;
    int scoreValue;

    float baseSpeedX;
    float baseSpeedY;
};
