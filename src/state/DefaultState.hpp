//
// Created by riebers on 14.12.2024.
//

#pragma once

#include "BaseState.hpp"
#include "gamer/Context.hpp"

namespace game {
    class DefaultState : public BaseState {
    private:
        Context &m_context;

    public:
        explicit DefaultState(Context &);

        DefaultState() = delete;

        void enter() override;

        void exit() override;

        void handle_events(SDL_Event const &) override;

        void update(entt::registry const &, const std::chrono::milliseconds &dt) override;

        void render(entt::registry const &) override;
    };
} // namespace game
