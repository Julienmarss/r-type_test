#pragma once

#include "Entity.hpp"
#include "SparseSet.hpp"
#include <tuple>

namespace rtype::engine {

    template<typename... Components>
    class View {
    public:
        View(SparseSet<Components>&... pools) : pools(pools...) {}

        class Iterator {
        public:
            Iterator(const std::vector<Entity>& entities, size_t index,
                     std::tuple<SparseSet<Components>&...>& pools)
                : entities(entities), index(index), pools(pools) {
                while (this->index < entities.size() && !isValid()) {
                    this->index++;
                }
            }

            auto operator*() {
                Entity entity = entities[index];
                return std::tuple_cat(
                    std::make_tuple(entity),
                    std::forward_as_tuple(*std::get<SparseSet<Components>&>(pools).get(entity)...)
                );
            }

            Iterator& operator++() {
                index++;
                while (index < entities.size() && !isValid()) {
                    index++;
                }
                return *this;
            }

            bool operator!=(const Iterator& other) const {
                return index != other.index;
            }

        private:
            bool isValid() const {
                Entity entity = entities[index];
                return (std::get<SparseSet<Components>&>(pools).has(entity) && ...);
            }

            const std::vector<Entity>& entities;
            size_t index;
            std::tuple<SparseSet<Components>&...>& pools;
        };

        Iterator begin() {
            const std::vector<Entity>* smallest = findSmallestPool();
            if (!smallest) {
                return end();
            }
            return Iterator(*smallest, 0, pools);
        }

        Iterator end() {
            const std::vector<Entity>* smallest = findSmallestPool();
            if (!smallest) {
                static std::vector<Entity> empty;
                return Iterator(empty, 0, pools);
            }
            return Iterator(*smallest, smallest->size(), pools);
        }

    private:
        const std::vector<Entity>* findSmallestPool() const {
            const std::vector<Entity>* smallest = nullptr;
            size_t minSize = SIZE_MAX;

            ((std::get<SparseSet<Components>&>(pools).size() < minSize ?
                (smallest = &std::get<SparseSet<Components>&>(pools).entities(),
                 minSize = std::get<SparseSet<Components>&>(pools).size()) :
                0), ...);

            return smallest;
        }

        std::tuple<SparseSet<Components>&...> pools;
    };

}
