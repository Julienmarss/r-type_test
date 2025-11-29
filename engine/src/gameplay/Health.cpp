#include "engine/gameplay/Health.hpp"

Health::Health()
    : maxHp(100.f), currentHp(100.f), invincible(false)
{
}

Health::Health(float maxHp)
    : maxHp(maxHp), currentHp(maxHp), invincible(false)
{
}
