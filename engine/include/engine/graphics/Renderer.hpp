#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

namespace rtype::engine {

class Renderer {
public:
    Renderer(int width, int height, const std::string& title);
    ~Renderer();

    void clear(sf::Color color);
    void display();
    
    bool isOpen() const;
    void close();
    
    bool pollEvent(sf::Event& event);
    
    sf::RenderWindow& getWindow();

private:
    std::unique_ptr<sf::RenderWindow> window;
};

}