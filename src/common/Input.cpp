//
// Created by Riebers on 09.02.2025.
//

#include "Input.hpp"

#include <ranges>
#include <SDL_events.h>
#include <SDL_keyboard.h>

namespace game {
    void Input::bind_keydown(SDL_Scancode key, ValidPredicate const &predicate, std::function<void()> const &callback) {
        Delegate<> delegator;
        delegator.bind(predicate, callback);
        m_keydown_actions.try_emplace(key, delegator);
    }

    void Input::bind_keypressed(SDL_Scancode key, ValidPredicate const &predicate,
                                std::function<void()> const &callback) {
        Delegate<> delegator;
        delegator.bind(predicate, callback);
        m_keypressed_actions.try_emplace(key, delegator);
    }

    void Input::bind_keyup(SDL_Scancode key, ValidPredicate const &predicate, std::function<void()> const &callback) {
        Delegate<> delegator;
        delegator.bind(predicate, callback);
        m_keyup_actions.try_emplace(key, delegator);
    }

    void Input::update() {
        Uint8 const *current_key_state = SDL_GetKeyboardState(nullptr);

        key_down_actions(current_key_state);
        key_pressed_actions(current_key_state);
        key_up_actions(current_key_state);
    }

    void Input::key_down_actions(Uint8 const *current_key_state) {
        for (auto &[keycode, delegator]: m_keydown_actions) {
            if (current_key_state[keycode]) {
                if (std::ranges::find(m_keypressed, keycode) == m_keypressed.end()) {
                    delegator.broadcast();
                    m_keypressed.emplace_back(keycode);
                }
            }
        }
        // add keypressed keys
        for (const auto &keycode: m_keypressed_actions | std::views::keys) {
            if (std::ranges::find(m_keypressed, keycode) == m_keypressed.end()) {
                if (current_key_state[keycode]) {
                    m_keypressed.emplace_back(keycode);
                }
            }
        }
        // add keyup keys
        for (const auto &keycode: m_keyup_actions | std::views::keys) {
            if (std::ranges::find(m_keypressed, keycode) == m_keypressed.end()) {
                if (current_key_state[keycode]) {
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
                }
            }
        }

        auto result = std::ranges::remove_if(m_keypressed, [current_key_state](SDL_Scancode key) {
            return !current_key_state[key];
        });
        m_keypressed.erase(result.begin(), result.end());
    }
}
