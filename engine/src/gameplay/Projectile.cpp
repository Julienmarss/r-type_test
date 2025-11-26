#include "engine/gameplay/Projectile.hpp"

Projectile::Projectile() 
    : type(ProjectileType::Normal), damage(10.f), piercing(false), isPlayerProjectile(true) {
}

Projectile::Projectile(ProjectileType type, float damage, bool piercing)
    : type(type), damage(damage), piercing(piercing), isPlayerProjectile(true) {
}