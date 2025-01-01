//
// Created by riebers on 14.12.2024.
//

#pragma once

#include "common/Button.hpp"
#include "common/Text.hpp"
#include "gamer/Context.hpp"

namespace game {
    class MenuState : public BaseState {
    private:
        ContextPtr m_context;
        std::vector<std::unique_ptr<Button> > m_buttons;
        std::unique_ptr<Text> m_text;
        std::function<void()> m_on_quit;

    public:
        explicit MenuState(ContextPtr, std::function<void()> on_quit);

        MenuState() = delete;

        void enter(Configuration const &) override;

        void exit() override;

        void handle_events(SDL_Event const &) override;

        void update(Registry const &, const std::chrono::milliseconds &dt) override;

        void render(Registry const &) override;
    };
} // namespace game
