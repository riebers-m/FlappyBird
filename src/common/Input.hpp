//
// Created by Riebers on 09.02.2025.
//

#pragma once
#include <SDL_scancode.h>

#include "Delegate.hpp"

namespace game {
    class Input {
    public:
        using ValidPredicate = std::function<bool()>;

        void bind_keydown(SDL_Scancode key, ValidPredicate const &predicate, std::function<void()> const &callback);

        void update();

    private:
        void key_down_actions(Uint8 const *current_key_state);

        void key_pressed_actions(Uint8 const *current_key_state);

        void key_up_actions(Uint8 const *current_key_state);

        std::vector<SDL_Scancode> m_keypressed;

        std::unordered_map<SDL_Scancode, Delegate<> > m_keydown_actions;
        std::unordered_map<SDL_Scancode, Delegate<> > m_keyup_actions;
        std::unordered_map<SDL_Scancode, Delegate<> > m_keypressed_actions;
    };
}
