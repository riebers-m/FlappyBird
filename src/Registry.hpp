//
// Created by Riebers on 24.01.2025.
//

#pragma once
#include "entity/Entity.hpp"
#include <entt/entt.hpp>

namespace registry {
    class Registry {
    private:
        entt::registry m_registry;

    public:
        Registry() = default;

        [[nodiscard]] entity::Entity create();
    };
} // registry
