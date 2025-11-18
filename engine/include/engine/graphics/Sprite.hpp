#pragma once

#include "../core/Component.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

namespace rtype::engine {

class Sprite : public Component {
public:
    Sprite();
    explicit Sprite(const std::string& texturePath);
    ~Sprite();

    bool loadTexture(const std::string& path);
    void setScale(float scaleX, float scaleY);
    void setPosition(float x, float y);
    
    sf::Sprite& getSprite();
    const sf::Sprite& getSprite() const;

private:
    std::unique_ptr<sf::Texture> texture;
    sf::Sprite sprite;
};

}