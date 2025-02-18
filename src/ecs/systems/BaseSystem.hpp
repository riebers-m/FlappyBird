//
// Created by Riebers on 18.02.2025.
//

#pragma once

namespace systems {
    class BaseSystem {
    public:
        explicit BaseSystem(entt::registry &registry) : m_registry{registry} {
        }

        virtual ~BaseSystem() = default;

    protected:
        entt::registry &m_registry;
    };
}
