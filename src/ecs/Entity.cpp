//
// Created by Riebers on 24.01.2025.
//

#include "ecs/Entity.hpp"

namespace ecs {
    Entity::Entity(entt::entity id, entt::registry &reg) : m_id(id), m_registry(reg) {
    }

    Entity Entity::create(entt::registry &registry) {
        auto const id = registry.create();
        return Entity{id, registry};
    }

    void Entity::destroy_all_entities(entt::registry &registry) {
        std::ranges::for_each(s_to_be_deleted_entities,
                              [&registry](entt::entity entity) {
                                  registry.destroy(entity);
                              });
        clear_to_be_deleted_entities();
    }


    void Entity::clear_to_be_deleted_entities() {
        s_to_be_deleted_entities.clear();
    }

    void Entity::destroy() {
        s_to_be_deleted_entities.emplace_back(m_id);
    }

    bool Entity::is_valid() const {
        return m_registry.valid(m_id);
    }
} // entity
