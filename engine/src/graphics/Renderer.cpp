#include "engine/graphics/Renderer.hpp"

namespace rtype::engine {

Renderer::Renderer(int width, int height, const std::string& title) {
    window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(width, height),
        title
    );
    window->setFramerateLimit(60);
}

Renderer::~Renderer() {
    if (window && window->isOpen()) {
        window->close();
    }
}

void Renderer::clear(sf::Color color) {
    window->clear(color);
}

void Renderer::display() {
    window->display();
}

bool Renderer::isOpen() const {
    return window->isOpen();
}

void Renderer::close() {
    window->close();
}

bool Renderer::pollEvent(sf::Event& event) {
    return window->pollEvent(event);
}

sf::RenderWindow& Renderer::getWindow() {
    return *window;
}

}