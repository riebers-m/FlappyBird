//
// Created by Riebers on 24.01.2025.
//

#include "Registry.hpp"

namespace registry {
    entity::Entity Registry::create() {
        auto const entity = m_registry.create();
        return entity::Entity{entity, this};
    }
} // registry
