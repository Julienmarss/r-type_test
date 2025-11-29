#include "engine/gameplay/Enemy.hpp"

Enemy::Enemy()
    : type(EnemyType::Basic), scoreValue(100), baseSpeedX(-150.f), baseSpeedY(0.f)
{
}

Enemy::Enemy(EnemyType type, int scoreValue)
    : type(type), scoreValue(scoreValue), baseSpeedX(-150.f), baseSpeedY(0.f)
{
}
