#include "engine/graphics/Sprite.hpp"
#include <iostream>

Sprite::Sprite() : texture(nullptr) {
}

Sprite::Sprite(const std::string& texturePath) : texture(nullptr) {
    loadTexture(texturePath);
}

Sprite::~Sprite() = default;

bool Sprite::loadTexture(const std::string& path) {
    // Créer une nouvelle texture avec shared_ptr
    texture = std::make_shared<sf::Texture>();
    
    if (!texture->loadFromFile(path)) {
        std::cerr << "❌ Failed to load texture: " << path << std::endl;
        texture.reset();
        return false;
    }
    
    // Lier le sprite à la texture
    sprite.setTexture(*texture, true);
    
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