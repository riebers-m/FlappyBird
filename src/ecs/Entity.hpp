//
// Created by Riebers on 24.01.2025.
//

#pragma once
#include <optional>
#include <entt/entt.hpp>

namespace ecs {
    class Entity {
    private:
        entt::registry &m_registry;
        entt::entity m_id;


        inline static std::vector<entt::entity> s_to_be_deleted_entities;

        static void clear_to_be_deleted_entities();

    public:
        explicit Entity(entt::entity id, entt::registry &reg);

        static Entity create(entt::registry &registry);

        static void destroy_all_entities(entt::registry &registry);

        void destroy();

        [[nodiscard]] bool is_valid() const;

        template<typename... Components>
        [[nodiscard]] bool has_components() const {
            return m_registry.all_of<Components...>(m_id);
        }

        template<typename Component, typename... TArgs>
        Component &add_component(TArgs &&... args) {
            return m_registry.emplace<Component>(m_id, std::forward<TArgs>(args)...);
        }

        template<typename... Components>
        void add_components() {
            (add_component<Components>(), ...);
        }

        template<typename Component, typename... TArgs>
        Component &replace(TArgs &&... args) {
            return m_registry.replace<Component>(m_id, std::forward<TArgs>(args)...);
        }

        template<typename Component>
        std::optional<Component> get_optional() const {
            if (m_registry.any_of<Component>(m_id)) {
                return m_registry.get<Component>(m_id);
            }
            return std::nullopt;
        }

        template<typename Component>
        Component &get_component() {
            return m_registry.get<Component>(m_id);
        }
    };
} // entity
