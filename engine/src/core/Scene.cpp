#include "engine/core/Scene.hpp"
#include "engine/core/Component.hpp"
#include "engine/graphics/Renderer.hpp"
#include <iostream>
#include <algorithm>

Scene::Scene() : nextEntityID(0) {
}

Scene::~Scene() = default;

Entity& Scene::createEntity() {
    auto entity = std::make_unique<Entity>(nextEntityID++);
    Entity& reference = *entity;
    entities.push_back(std::move(entity));
    return reference;
}

const std::vector<std::unique_ptr<Entity>>& Scene::getEntities() const {
    return entities;
}

void Scene::markEntityForDestruction(EntityID id) {
    markedForDestruction.push_back(id);
}

void Scene::cleanupMarkedEntities() {
    if (markedForDestruction.empty()) return;
    
    int count = markedForDestruction.size();
    
    entities.erase(
        std::remove_if(entities.begin(), entities.end(),
            [this](const std::unique_ptr<Entity>& entity) {
                return std::find(markedForDestruction.begin(), markedForDestruction.end(), 
                                entity->getID()) != markedForDestruction.end();
            }),
        entities.end()
    );
    
    std::cout << "🗑️  Destroyed " << count << " entities" << std::endl;  // ✅ DEBUG
    
    markedForDestruction.clear();
}

void Scene::addSystem(std::unique_ptr<System> system) {
    systems.push_back(std::move(system));
}

void Scene::update(float deltaTime) {
    for (auto& system : systems) {
        system->update(deltaTime, entities);
    }
    
    cleanupMarkedEntities();
}

void Scene::render(Renderer& renderer) {
    for (auto& system : systems) {
        system->render(renderer, entities);
    }
}