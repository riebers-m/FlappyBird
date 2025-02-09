//
// Created by Riebers on 09.02.2025.
//

#include "Input.hpp"

#include <SDL_keyboard.h>

namespace game {
    void Input::update() {
        Uint8 const *const current_key_state = SDL_GetKeyboardState(nullptr);

        key_down_actions(current_key_state);
        key_pressed_actions(current_key_state);
        key_up_actions(current_key_state);
    }

    void Input::key_down_actions(Uint8 const *const current_key_state) {
        for (auto &[keycode, delegator]: m_keydown_actions) {
            if (current_key_state[keycode]) {
                if (std::ranges::find(m_keypressed, keycode) == m_keypressed.end()) {
                    delegator.broadcast();
                    m_keypressed.emplace_back(keycode);
                }
            }
        }
    }

    void Input::key_pressed_actions(Uint8 const *current_key_state) {
        for (auto &[keycode, delegator]: m_keypressed_actions) {
            if (current_key_state[keycode]) {
                if (std::ranges::find(m_keypressed, keycode) != m_keypressed.end()) {
                    delegator.broadcast();
                }
            }
        }
    }

    void Input::key_up_actions(Uint8 const *current_key_state) {
        for (auto &[keycode, delegator]: m_keyup_actions) {
            if (!current_key_state[keycode]) {
                if (auto itr = std::ranges::find(m_keypressed, keycode); itr != m_keypressed.end()) {
                    delegator.broadcast();
                    m_keypressed.erase(itr);
                }
            }
        }
    }
}
