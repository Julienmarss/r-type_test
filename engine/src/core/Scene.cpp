#include "engine/core/Scene.hpp"
#include "engine/graphics/Renderer.hpp"

namespace rtype::engine {

Scene::Scene() : nextEntityID(0) {
}

Scene::~Scene() {
}

Entity& Scene::createEntity() {
    std::unique_ptr<Entity> entity = std::make_unique<Entity>(nextEntityID++);
    Entity& reference = *entity;
    entities.push_back(std::move(entity));
    return reference;
}

const std::vector<std::unique_ptr<Entity>>& Scene::getEntities() const {
    return entities;
}

void Scene::addSystem(std::unique_ptr<System> system) {
    systems.push_back(std::move(system));
}

void Scene::update(float deltaTime) {
    for (std::unique_ptr<System>& system : systems) {
        system->update(deltaTime, entities);
    }
}

void Scene::render(Renderer& renderer) {
    for (std::unique_ptr<System>& system : systems) {
        system->render(renderer, entities);
    }
}

}