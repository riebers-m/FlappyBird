//
// Created by riebers on 14.12.2024.
//

#pragma once
#include <chrono>
#include "SDL_events.h"
#include "ecs/Entity.hpp"

namespace game {
    class BaseState {
    protected:
        bool m_transparent{false};

    public:
        virtual ~BaseState() = default;

        virtual void enter() = 0;

        virtual void exit() = 0;

        virtual void handle_events(SDL_Event const &) = 0;

        virtual void update(entt::registry const &,
                            std::chrono::milliseconds const &dt) = 0;

        virtual void render(entt::registry const &) = 0;

        void set_transparent(bool transparent) { m_transparent = transparent; }

        [[nodiscard]] bool is_transparent() const { return m_transparent; }
    };
} // namespace game
