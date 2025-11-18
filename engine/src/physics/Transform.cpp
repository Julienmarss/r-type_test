#include "engine/physics/Transform.hpp"

namespace rtype::engine {

Transform::Transform() 
    : x(0.f), y(0.f), rotation(0.f), scaleX(1.f), scaleY(1.f) {
}

Transform::Transform(float x, float y) 
    : x(x), y(y), rotation(0.f), scaleX(1.f), scaleY(1.f) {
}

}