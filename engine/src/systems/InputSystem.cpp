#include "engine/systems/InputSystem.hpp"
#include "engine/core/Entity.hpp"
#include "engine/graphics/Renderer.hpp"
#include "engine/physics/Velocity.hpp"
#include "engine/gameplay/Controllable.hpp"
#include <SFML/Window/Keyboard.hpp>

InputSystem::InputSystem(Renderer& renderer) 
    : renderer(renderer) {
}

void InputSystem::update(float deltaTime, const std::vector<std::unique_ptr<Entity>>& entities) {
    for (const auto& entity : entities) {
        auto* controllable = entity->getComponent<Controllable>();
        auto* velocity = entity->getComponent<Velocity>();
        
        if (!controllable || !velocity) continue;
        
        velocity->x = 0.f;
        velocity->y = 0.f;
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || 
            sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            velocity->x = -controllable->speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || 
            sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            velocity->x = controllable->speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || 
            sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            velocity->y = -controllable->speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || 
            sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            velocity->y = controllable->speed;
        }
        
        if (controllable->currentCooldown > 0.f) {
            controllable->currentCooldown -= deltaTime;
        }
    }
}