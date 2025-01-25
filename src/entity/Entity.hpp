//
// Created by Riebers on 24.01.2025.
//

#pragma once
#include <cstdint>

namespace entt {
    enum class entity : std::uint32_t;
}

namespace registry {
    class Registry;
}

namespace entity {
    class Entity {
    private:
        registry::Registry *m_registry;
        entt::entity m_id;

        explicit Entity(entt::entity id, registry::Registry *reg);

    public:
        // template<typename... TComponents>
        // void add_component(TComponents &&... components) {
        //     m_
        // }

        friend class registry::Registry;
    };
} // entity
