#pragma once
#include "engine/core/System.hpp"

class BoundarySystem : public System {
public:
    BoundarySystem(float minX, float maxX, float minY, float maxY);
    
    void update(float deltaTime, const std::vector<std::unique_ptr<Entity>>& entities) override;

private:
    float minX;
    float maxX;
    float minY;
    float maxY;
};