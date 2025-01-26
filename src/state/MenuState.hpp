//
// Created by riebers on 14.12.2024.
//

#pragma once

#include "BaseState.hpp"
#include "common/Button.hpp"
#include "common/Text.hpp"
#include "gamer/Context.hpp"

namespace game {
    class MenuState : public BaseState {
    private:
        Context m_context;
        std::vector<std::unique_ptr<Button> > m_buttons;
        std::unique_ptr<Text> m_text;
        std::function<void()> m_on_quit;

    public:
        explicit MenuState(Context, std::function<void()> on_quit);

        MenuState() = delete;

        void enter() override;

        void exit() override;

        void handle_events(SDL_Event const &) override;

        void update(entt::registry const &, const std::chrono::milliseconds &dt) override;

        void render(entt::registry const &) override;
    };
} // namespace game
