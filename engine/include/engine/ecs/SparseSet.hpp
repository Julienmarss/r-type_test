#pragma once

#include "Entity.hpp"
#include <vector>

namespace rtype::engine {

    template<typename Component>
    class SparseSet {
    public:
        template<typename... Args>
        Component& emplace(Entity entity, Args&&... args) {
            if (entity >= sparse.size()) {
                sparse.resize(entity + 1, NULL_ENTITY);
            }

            if (sparse[entity] != NULL_ENTITY) {
                size_t index = sparse[entity];
                components[index] = Component(std::forward<Args>(args)...);
                return components[index];
            }

            size_t index = dense.size();
            sparse[entity] = index;
            dense.push_back(entity);
            components.emplace_back(std::forward<Args>(args)...);
            return components.back();
        }

        void remove(Entity entity) {
            if (entity >= sparse.size() || sparse[entity] == NULL_ENTITY) {
                return;
            }

            size_t index = sparse[entity];
            Entity lastEntity = dense.back();

            dense[index] = lastEntity;
            components[index] = std::move(components.back());
            sparse[lastEntity] = index;

            dense.pop_back();
            components.pop_back();
            sparse[entity] = NULL_ENTITY;
        }

        Component* get(Entity entity) {
            if (entity >= sparse.size() || sparse[entity] == NULL_ENTITY) {
                return nullptr;
            }
            return &components[sparse[entity]];
        }

        const Component* get(Entity entity) const {
            if (entity >= sparse.size() || sparse[entity] == NULL_ENTITY) {
                return nullptr;
            }
            return &components[sparse[entity]];
        }

        bool has(Entity entity) const {
            return entity < sparse.size() && sparse[entity] != NULL_ENTITY;
        }

        size_t size() const {
            return dense.size();
        }

        auto begin() { return components.begin(); }
        auto end() { return components.end(); }
        auto begin() const { return components.begin(); }
        auto end() const { return components.end(); }

        const std::vector<Entity>& entities() const { return dense; }

        void clear() {
            sparse.clear();
            dense.clear();
            components.clear();
        }

    private:
        std::vector<Entity> sparse;
        std::vector<Entity> dense;
        std::vector<Component> components;
    };

}
