#include "engine/graphics/BackgroundManager.hpp"
#include "engine/core/Scene.hpp"
#include "engine/core/Entity.hpp"
#include "engine/graphics/Sprite.hpp"
#include "engine/physics/Transform.hpp"
#include "engine/physics/Velocity.hpp"
#include <SFML/Graphics.hpp>

namespace rtype::engine {

BackgroundManager::BackgroundManager(Scene& scene, float windowWidth, float windowHeight)
    : scene(scene), windowWidth(windowWidth), windowHeight(windowHeight) {
}

void BackgroundManager::addScrollingBackground(const std::string& imagePath, float scrollSpeed) {
    sf::Image tempImage;
    if (!tempImage.loadFromFile(imagePath)) {
        return;
    }

    float imgW = static_cast<float>(tempImage.getSize().x);
    float imgH = static_cast<float>(tempImage.getSize().y);
    float scale = 1.0f;
    float offsetX = 0.0f;
    float offsetY = (windowHeight - imgH) / 2.0f;

    Entity& bg1 = scene.createEntity();
    bg1.addComponent("Sprite", std::make_unique<Sprite>(imagePath));

    auto t1 = std::make_unique<Transform>(offsetX, offsetY);
    t1->scaleX = scale;
    t1->scaleY = scale;
    bg1.addComponent("Transform", std::move(t1));
    bg1.addComponent("Velocity", std::make_unique<Velocity>(scrollSpeed, 0.0f));

    Entity& bg2 = scene.createEntity();
    bg2.addComponent("Sprite", std::make_unique<Sprite>(imagePath));

    auto t2 = std::make_unique<Transform>(offsetX + imgW, offsetY);
    t2->scaleX = scale;
    t2->scaleY = scale;
    bg2.addComponent("Transform", std::move(t2));
    bg2.addComponent("Velocity", std::make_unique<Velocity>(scrollSpeed, 0.0f));

    BackgroundLayer layer;
    layer.entity1 = &bg1;
    layer.entity2 = &bg2;
    layer.scrollSpeed = scrollSpeed;
    layer.imageWidth = imgW;
    layer.scale = scale;

    layers.push_back(layer);
}

void BackgroundManager::update() {
    for (BackgroundLayer& layer : layers) {
        Transform* t1 = static_cast<Transform*>(layer.entity1->getComponent("Transform"));
        Transform* t2 = static_cast<Transform*>(layer.entity2->getComponent("Transform"));

        if (!t1 || !t2)
            continue;

        float realWidth = layer.imageWidth * layer.scale;

        if (t1->x + realWidth <= 0.0f) {
            t1->x = t2->x + realWidth;
        }
        if (t2->x + realWidth <= 0.0f) {
            t2->x = t1->x + realWidth;
        }
    }
}

}
