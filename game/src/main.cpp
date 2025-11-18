#include <engine/graphics/Renderer.hpp>
#include <engine/core/Scene.hpp>
#include <engine/core/Entity.hpp>
#include <engine/graphics/Sprite.hpp>
#include <engine/physics/Transform.hpp>
#include <engine/systems/RenderSystem.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <cmath>

int main() {
    const float windowWidth = 1280.f;
    const float windowHeight = 720.f;

    rtype::engine::Renderer renderer(windowWidth, windowHeight, "R-Type");
    rtype::engine::Scene scene;
    scene.addSystem(std::make_unique<rtype::engine::RenderSystem>());

    sf::Texture debugTexture;
    if (!debugTexture.loadFromFile("assets/sprites/background.png")) {
        std::cerr << "ERROR: Unable to load background.png\n";
        return 1;
    }

    const float bgW = debugTexture.getSize().x;
    const float bgH = debugTexture.getSize().y;
    const float scale = 1.0f;
    float displayedW = bgW * scale;
    float displayedH = bgH * scale;
    float offsetY = (windowHeight - displayedH) / 2.0f;
    float scrollOffset = 0.f;
    float scrollSpeed = 100.f;

    rtype::engine::Entity& bg1 = scene.createEntity();
    bg1.addComponent("Sprite", std::make_unique<rtype::engine::Sprite>("assets/sprites/background.png"));
    auto t1 = std::make_unique<rtype::engine::Transform>(0, offsetY);
    t1->scaleX = scale;
    t1->scaleY = scale;
    bg1.addComponent("Transform", std::move(t1));

    rtype::engine::Entity& bg2 = scene.createEntity();
    bg2.addComponent("Sprite", std::make_unique<rtype::engine::Sprite>("assets/sprites/background.png"));
    auto t2 = std::make_unique<rtype::engine::Transform>(displayedW, offsetY);
    t2->scaleX = scale;
    t2->scaleY = scale;
    bg2.addComponent("Transform", std::move(t2));

    sf::Clock clock;

    while (renderer.isOpen()) {
        float dt = clock.restart().asSeconds();

        sf::Event event;
        while (renderer.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                renderer.close();
        }

        scrollOffset -= scrollSpeed * dt;

        float x1 = fmod(scrollOffset, displayedW);
        if (x1 > 0)
            x1 -= displayedW;

        float x2 = x1 + displayedW;

        auto tr1 = static_cast<rtype::engine::Transform*>(bg1.getComponent("Transform"));
        auto tr2 = static_cast<rtype::engine::Transform*>(bg2.getComponent("Transform"));

        tr1->x = x1;
        tr2->x = x2;

        static float logTimer = 0.f;
        logTimer += dt;
        if (logTimer >= 1.f) {
            logTimer = 0.f;
        }

        renderer.clear(sf::Color::Black);
        scene.render(renderer);
        renderer.display();
    }

    return 0;
}
