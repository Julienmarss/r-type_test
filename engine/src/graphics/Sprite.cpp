#include "engine/graphics/Sprite.hpp"
#include <iostream>

namespace rtype::engine {

Sprite::Sprite() : texture(nullptr) {
}

Sprite::Sprite(const std::string& texturePath) : texture(nullptr) {
    loadTexture(texturePath);
}

Sprite::~Sprite() {
}

bool Sprite::loadTexture(const std::string& path) {
    texture = std::make_unique<sf::Texture>();
    
    if (!texture->loadFromFile(path)) {
        std::cerr << "Failed to load texture: " << path << std::endl;
        return false;
    }
    
    sprite.setTexture(*texture);
    return true;
}

void Sprite::setScale(float scaleX, float scaleY) {
    sprite.setScale(scaleX, scaleY);
}

void Sprite::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

sf::Sprite& Sprite::getSprite() {
    return sprite;
}

const sf::Sprite& Sprite::getSprite() const {
    return sprite;
}

}