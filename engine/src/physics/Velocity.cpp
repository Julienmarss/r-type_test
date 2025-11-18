#include "engine/physics/Velocity.hpp"

namespace rtype::engine {

Velocity::Velocity() : x(0.f), y(0.f) {
}

Velocity::Velocity(float vx, float vy) : x(vx), y(vy) {
}

}