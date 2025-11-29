#include "engine/systems/ShootingSystem.hpp"
#include "engine/core/Entity.hpp"
#include "engine/core/Scene.hpp"
#include "engine/graphics/Sprite.hpp"
#include "engine/physics/Transform.hpp"
#include "engine/physics/Velocity.hpp"
#include "engine/physics/Hitbox.hpp"
#include "engine/gameplay/Controllable.hpp"
#include "engine/gameplay/Projectile.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

ShootingSystem::ShootingSystem(Scene& scene, float windowWidth)
    : scene(scene), windowWidth(windowWidth), chargeTime(0.f), wasSpacePressed(false) {
}

void ShootingSystem::update(float deltaTime, const std::vector<std::unique_ptr<Entity>>& entities) {
    bool spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

    std::vector<Entity*> shooters;
    shooters.reserve(entities.size());
    for (const auto& entity : entities) {
        auto* controllable = entity->getComponent<Controllable>();
        auto* transform = entity->getComponent<Transform>();
        if (!controllable || !transform)
            continue;
        shooters.push_back(entity.get());
    }

    for (Entity* entity : shooters) {
        auto* controllable = entity->getComponent<Controllable>();
        auto* transform = entity->getComponent<Transform>();
        if (!controllable || !transform)
            continue;

        if (controllable->currentCooldown > 0.f) {
            controllable->currentCooldown -= deltaTime;
        }

        if (spacePressed) {
            chargeTime += deltaTime;
        }

        if (!spacePressed && wasSpacePressed) {
            if (controllable->canShoot && controllable->currentCooldown <= 0.f) {
                float shootX = transform->x + 180.f;
                float shootY = transform->y + 40.f;

                if (chargeTime >= 2.0f) {
                    std::cout << "CHARGED SHOT!" << std::endl;
                    createChargedShot(shootX, shootY);
                    controllable->currentCooldown = 1.5f;
                } else if (chargeTime > 0.f) {
                    std::cout << "Normal shot" << std::endl;
                    createNormalShot(shootX, shootY);
                    controllable->currentCooldown = 0.25f;
                }

                chargeTime = 0.f;
            }
        }
    }

    wasSpacePressed = spacePressed;

    cleanupOffscreenProjectiles(entities);
}

void ShootingSystem::createNormalShot(float x, float y) {
    std::cout << "  → Creating normal bullet at " << x << ", " << y << std::endl;
    
    Entity& bullet = scene.createEntity();
    
    auto sprite = std::make_unique<Sprite>();
    if (!sprite->loadTexture("assets/sprites/bullet_normal.png")) {
        std::cerr << "ERROR: Failed to load bullet_normal.png!" << std::endl;
        return;
    }
    bullet.addComponent(std::move(sprite));
    
    // Dimensions: 64×43
    auto transform = std::make_unique<Transform>(x, y - 21.f);
    transform->scaleX = 1.0f;
    transform->scaleY = 1.0f;
    bullet.addComponent(std::move(transform));
    
    bullet.addComponent(std::make_unique<Velocity>(700.f, 0.f));
    bullet.addComponent(std::make_unique<Projectile>(ProjectileType::Normal, 10.f, false));
    bullet.addComponent(std::make_unique<Hitbox>(64.f, 43.f));
    
    std::cout << "  Normal bullet created!" << std::endl;
}

void ShootingSystem::createChargedShot(float x, float y) {
    std::cout << "  → Creating charged bullet at " << x << ", " << y << std::endl;
    
    Entity& bullet = scene.createEntity();
    
    auto sprite = std::make_unique<Sprite>();
    if (!sprite->loadTexture("assets/sprites/bullet_charged.png")) {
        std::cerr << "ERROR: Failed to load bullet_charged.png!" << std::endl;
        return;
    }
    bullet.addComponent(std::move(sprite));
    
    auto transform = std::make_unique<Transform>(x, y - 42.f);
    transform->scaleX = 1.0f;
    transform->scaleY = 1.0f;
    bullet.addComponent(std::move(transform));
    
    bullet.addComponent(std::make_unique<Velocity>(500.f, 0.f));
    bullet.addComponent(std::make_unique<Projectile>(ProjectileType::Charged, 50.f, true));
    bullet.addComponent(std::make_unique<Hitbox>(128.f, 85.f));
    
    std::cout << "  Charged bullet created!" << std::endl;
}

void ShootingSystem::cleanupOffscreenProjectiles(const std::vector<std::unique_ptr<Entity>>& entities) {
    for (const auto& entity : entities) {
        auto* projectile = entity->getComponent<Projectile>();
        auto* transform = entity->getComponent<Transform>();
        
        if (projectile && transform) {
            if (transform->x > windowWidth + 100.f) {
                scene.markEntityForDestruction(entity->getID());
            }
        }
    }
}