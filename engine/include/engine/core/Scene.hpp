#pragma once
#include "Entity.hpp"
#include "System.hpp"
#include <vector>
#include <memory>

class Renderer;

class Scene {
public:
    Scene();
    ~Scene();

    Entity& createEntity();
    const std::vector<std::unique_ptr<Entity>>& getEntities() const;
    
    void markEntityForDestruction(EntityID id);
    void cleanupMarkedEntities();

    void addSystem(std::unique_ptr<System> system);
    void update(float deltaTime);
    void render(Renderer& renderer);

private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<EntityID> markedForDestruction;
    std::vector<std::unique_ptr<System>> systems;
    EntityID nextEntityID;
};