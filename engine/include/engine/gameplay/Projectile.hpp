#pragma once
#include "engine/core/Component.hpp"

enum class ProjectileType {
    Normal,
    Charged
};

class Projectile : public Component {
public:
    Projectile();
    Projectile(ProjectileType type, float damage, bool piercing);

    ProjectileType type;
    float damage;
    bool piercing;
    bool isPlayerProjectile;
};