#pragma once
#include "Component.hpp"
#include <cstdint>
#include <unordered_map>
#include <memory>
#include <typeindex>

using EntityID = uint32_t;

class Entity {
public:
    explicit Entity(EntityID id);
    
    EntityID getID() const;
    
    template<typename T>
    void addComponent(std::unique_ptr<T> component);
    
    template<typename T>
    T* getComponent();
    
    template<typename T>
    bool hasComponent() const;

private:
    EntityID id;
    std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
};

#include "Entity.inl"