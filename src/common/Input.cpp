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

    void Input::bind_mouse_down(MouseButtons button, ValidPredicate const &predicate,
                                std::function<void(int, int)> const &callback) {
        Delegate<int, int> delegator;
        delegator.bind(predicate, callback);
        m_mouse_down_actions.try_emplace(static_cast<Uint8>(button), delegator);
    }

    void Input::bind_mouse_up(MouseButtons button, ValidPredicate const &predicate,
                              std::function<void(int, int)> const &callback) {
        Delegate<int, int> delegator;
        delegator.bind(predicate, callback);
        m_mouse_up_actions.try_emplace(static_cast<Uint8>(button), delegator);
    }

    void Input::bind_mouse_pressed(MouseButtons button, ValidPredicate const &predicate,
                                   std::function<void(int, int)> const &callback) {
        Delegate<int, int> delegator;
        delegator.bind(predicate, callback);
        m_mouse_pressed_actions.try_emplace(static_cast<Uint8>(button), delegator);
    }

    void Input::update() {
        Uint8 const *current_key_state = SDL_GetKeyboardState(nullptr);

        key_down_actions(current_key_state);
        key_pressed_actions(current_key_state);
        key_up_actions(current_key_state);

        int x_pos, y_pos;
        auto const mouse_mask = SDL_GetMouseState(&x_pos, &y_pos);
        mouse_down_actions(mouse_mask, x_pos, y_pos);
        mouse_pressed_actions(mouse_mask, x_pos, y_pos);
        mouse_up_actions(mouse_mask, x_pos, y_pos);
    }

    void Input::handle_events(SDL_Event event) {
        if (event.type == SDL_MOUSEMOTION) {
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        } else if (event.type == SDL_MOUSEBUTTONUP) {
        }
    }

    bool Input::is_key_down(SDL_Scancode key) {
        return SDL_GetKeyboardState(nullptr)[key];
    }

    bool Input::is_key_up(SDL_Scancode key) {
        return !is_key_down(key);
    }

    bool Input::is_mouse_down(MouseButtons mouse_button) {
        auto const button_state = SDL_GetMouseState(nullptr, nullptr);
        return button_state & SDL_BUTTON(static_cast<uint32_t>(mouse_button));
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

    void Input::mouse_down_actions(Uint32 mouse_mask, int x_pos, int y_pos) {
        for (auto &[button, delegator]: m_mouse_down_actions) {
            if (mouse_mask & SDL_BUTTON(button)) {
                if (std::ranges::find(m_mousepressed, button) == m_mousepressed.end()) {
                    delegator.broadcast(x_pos, y_pos);
                    m_mousepressed.emplace_back(button);
                }
            }
        }

        for (auto const &button: m_mouse_up_actions | std::views::keys) {
            if (mouse_mask & SDL_BUTTON(button)) {
                if (std::ranges::find(m_mousepressed, button) == m_mousepressed.end()) {
                    m_mousepressed.emplace_back(button);
                }
            }
        }

        for (auto const &button: m_mouse_pressed_actions | std::views::keys) {
            if (mouse_mask & SDL_BUTTON(button)) {
                if (std::ranges::find(m_mousepressed, button) == m_mousepressed.end()) {
                    m_mousepressed.emplace_back(button);
                }
            }
        }
    }

    void Input::mouse_pressed_actions(Uint32 mouse_mask, int x_pos, int y_pos) {
        for (auto &[button, delegator]: m_mouse_pressed_actions) {
            if (mouse_mask & SDL_BUTTON(button)) {
                if (std::ranges::find(m_mousepressed, button) != m_mousepressed.end()) {
                    delegator.broadcast(x_pos, y_pos);
                }
            }
        }
    }

    void Input::mouse_up_actions(Uint32 mouse_mask, int x_pos, int y_pos) {
        for (auto &[button, delegator]: m_mouse_up_actions) {
            if (!(mouse_mask & SDL_BUTTON(button))) {
                if (auto itr = std::ranges::find(m_mousepressed, button); itr != m_mousepressed.end()) {
                    delegator.broadcast(x_pos, y_pos);
                }
            }
        }

        auto result = std::ranges::remove_if(m_mousepressed, [mouse_mask](Uint32 button) {
            return !(mouse_mask & SDL_BUTTON(button));
        });
        m_mousepressed.erase(result.begin(), result.end());
    }
}
