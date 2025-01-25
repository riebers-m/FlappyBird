//
// Created by Riebers on 24.01.2025.
//

#include "Entity.hpp"

namespace entity {
    Entity::Entity(entt::entity id, registry::Registry *reg) : m_id(id), m_registry(reg) {
    }
} // entity
