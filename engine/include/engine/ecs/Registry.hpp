#pragma once

#include "Entity.hpp"
#include "SparseSet.hpp"
#include "View.hpp"
#include <any>
#include <typeindex>
#include <unordered_map>
#include <queue>

namespace rtype::engine {

    class Registry {
    public:
        Registry() : nextEntityID(0) {}

        Entity create() {
            Entity entity;
            if (!freeEntities.empty()) {
                entity = freeEntities.front();
                freeEntities.pop();
            } else {
                entity = nextEntityID++;
            }
            return entity;
        }

        void destroy(Entity entity) {
            freeEntities.push(entity);
        }

        template<typename Component, typename... Args>
        Component& add(Entity entity, Args&&... args) {
            return getPool<Component>().emplace(entity, std::forward<Args>(args)...);
        }

        template<typename Component>
        void remove(Entity entity) {
            getPool<Component>().remove(entity);
        }

        template<typename Component>
        Component* get(Entity entity) {
            return getPool<Component>().get(entity);
        }

        template<typename Component>
        const Component* get(Entity entity) const {
            return const_cast<Registry*>(this)->getPool<Component>().get(entity);
        }

        template<typename Component>
        bool has(Entity entity) const {
            return const_cast<Registry*>(this)->getPool<Component>().has(entity);
        }

        template<typename... Components>
        View<Components...> view() {
            return View<Components...>(getPool<Components>()...);
        }

        void clear() {
            pools.clear();
            while (!freeEntities.empty()) {
                freeEntities.pop();
            }
            nextEntityID = 0;
        }

        size_t size() const {
            return nextEntityID - freeEntities.size();
        }

    private:
        template<typename Component>
        SparseSet<Component>& getPool() {
            auto typeIndex = std::type_index(typeid(Component));
            if (pools.find(typeIndex) == pools.end()) {
                pools[typeIndex] = SparseSet<Component>();
            }
            return std::any_cast<SparseSet<Component>&>(pools[typeIndex]);
        }

        std::unordered_map<std::type_index, std::any> pools;
        Entity nextEntityID;
        std::queue<Entity> freeEntities;
    };

}
