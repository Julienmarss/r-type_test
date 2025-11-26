#pragma once
#include "engine/core/System.hpp"

class ScrollingBackgroundSystem : public System {
public:
    explicit ScrollingBackgroundSystem(float windowWidth);
    
    void update(float deltaTime, const std::vector<std::unique_ptr<Entity>>& entities) override;

private:
    float windowWidth;
};