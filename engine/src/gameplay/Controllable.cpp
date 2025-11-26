#include "engine/gameplay/Controllable.hpp"

Controllable::Controllable() 
    : speed(300.f), canShoot(true), shootCooldown(0.2f), currentCooldown(0.f) {
}

Controllable::Controllable(float speed) 
    : speed(speed), canShoot(true), shootCooldown(0.2f), currentCooldown(0.f) {
}