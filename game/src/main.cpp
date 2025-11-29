#include <engine/graphics/Renderer.hpp>
#include <engine/core/Scene.hpp>
#include <engine/core/Entity.hpp>
#include <engine/graphics/Sprite.hpp>
#include <engine/physics/Transform.hpp>
#include <engine/physics/Velocity.hpp>
#include <engine/physics/Hitbox.hpp>
#include <engine/gameplay/Controllable.hpp>
#include <engine/gameplay/Health.hpp>
#include <engine/gameplay/Enemy.hpp>
#include <engine/systems/RenderSystem.hpp>
#include <engine/systems/MovementSystem.hpp>
#include <engine/systems/ScrollingBackgroundSystem.hpp>
#include <engine/systems/InputSystem.hpp>
#include <engine/systems/BoundarySystem.hpp>
#include <engine/systems/ShootingSystem.hpp>
#include <engine/systems/EnemySpawnSystem.hpp>
#include <engine/systems/EnemyBehaviorSystem.hpp>
#include <engine/systems/CollisionSystem.hpp>
#include <engine/systems/EnemyVisualSystem.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

int main() {
    const float windowWidth = 1280.f;
    const float windowHeight = 720.f;

    Renderer renderer(windowWidth, windowHeight, "R-Type");
    Scene scene;
    
    // === SYSTEMS ===
    scene.addSystem(std::make_unique<InputSystem>(renderer));
    scene.addSystem(std::make_unique<ShootingSystem>(scene, windowWidth));
    scene.addSystem(std::make_unique<EnemySpawnSystem>(scene, windowWidth, windowHeight));
    scene.addSystem(std::make_unique<EnemyBehaviorSystem>());
    scene.addSystem(std::make_unique<MovementSystem>());
    scene.addSystem(std::make_unique<CollisionSystem>(scene));
    scene.addSystem(std::make_unique<EnemyVisualSystem>());
    scene.addSystem(std::make_unique<BoundarySystem>(0.f, windowWidth - 130.f, 0.f, windowHeight - 90.f));
    scene.addSystem(std::make_unique<ScrollingBackgroundSystem>(windowWidth));
    scene.addSystem(std::make_unique<RenderSystem>());

    // === BACKGROUND ===
    Entity& bg1 = scene.createEntity();
    bg1.addComponent(std::make_unique<Sprite>("assets/sprites/background.png"));
    bg1.addComponent(std::make_unique<Transform>(0.f, 0.f));
    bg1.addComponent(std::make_unique<Velocity>(-100.f, 0.f));

    Entity& bg2 = scene.createEntity();
    bg2.addComponent(std::make_unique<Sprite>("assets/sprites/background.png"));
    bg2.addComponent(std::make_unique<Transform>(windowWidth, 0.f));
    bg2.addComponent(std::make_unique<Velocity>(-100.f, 0.f));

    // === PLAYER ===
    Entity& player = scene.createEntity();
    
    auto playerSprite = std::make_unique<Sprite>("assets/sprites/player.png");
    playerSprite->getSprite().setTextureRect(sf::IntRect(0, 30, 316, 160));
    player.addComponent(std::move(playerSprite));
    
    auto playerTransform = std::make_unique<Transform>(100.f, windowHeight / 2.f - 80.f);
    playerTransform->scaleX = 0.5f;
    playerTransform->scaleY = 0.5f;
    player.addComponent(std::move(playerTransform));
    
    player.addComponent(std::make_unique<Velocity>(0.f, 0.f));
    player.addComponent(std::make_unique<Controllable>(250.f));
    player.addComponent(std::make_unique<Health>(100.f));
    player.addComponent(std::make_unique<Hitbox>(120.f, 80.f));

    std::cout << "=== R-TYPE CLIENT ===" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  Move: Arrow Keys or ZQSD" << std::endl;
    std::cout << "  Shoot: TAP Space (normal)" << std::endl;
    std::cout << "  Charged Shot: HOLD Space 2s (piercing)" << std::endl;

    sf::Clock clock;

    while (renderer.isOpen()) {
        float dt = clock.restart().asSeconds();

        sf::Event event;
        while (renderer.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                renderer.close();
            }
        }

        scene.update(dt);

        renderer.clear(sf::Color::Black);
        scene.render(renderer);
        renderer.display();
    }

    return 0;
}