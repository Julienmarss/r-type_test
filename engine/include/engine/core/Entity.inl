#pragma once

template<typename T>
void Entity::addComponent(std::unique_ptr<T> component) {
    components[std::type_index(typeid(T))] = std::move(component);
}

template<typename T>
T* Entity::getComponent() {
    auto it = components.find(std::type_index(typeid(T)));
    if (it != components.end()) {
        return static_cast<T*>(it->second.get());
    }
    return nullptr;
}

template<typename T>
bool Entity::hasComponent() const {
    return components.find(std::type_index(typeid(T))) != components.end();
}