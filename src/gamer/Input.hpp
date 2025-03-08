//
// Created by Riebers on 09.02.2025.
//

#pragma once
#include <SDL_events.h>
#include <SDL_scancode.h>
#include <cstdint>

#include "Delegate.hpp"

namespace game {
    enum class MouseButtons : std::uint32_t { left = 1, middle, right };

    class Input {
    public:
        using ValidPredicate = std::function<bool()>;

        void bind_keydown(SDL_Scancode key, ValidPredicate const &predicate,
                          std::function<void()> const &callback);

        void bind_keypressed(SDL_Scancode key, ValidPredicate const &predicate,
                             std::function<void()> const &callback);

        void bind_keyup(SDL_Scancode key, ValidPredicate const &predicate,
                        std::function<void()> const &callback);

        void bind_mouse_down(MouseButtons button,
                             ValidPredicate const &predicate,
                             std::function<void(int, int)> const &callback);

        void bind_mouse_up(MouseButtons button, ValidPredicate const &predicate,
                           std::function<void(int, int)> const &callback);

        void bind_mouse_pressed(MouseButtons button,
                                ValidPredicate const &predicate,
                                std::function<void(int, int)> const &callback);


        void update();

        void handle_events(SDL_Event event);

        [[nodiscard]] static bool is_key_down(SDL_Scancode key);

        [[nodiscard]] static bool is_key_up(SDL_Scancode key);

        [[nodiscard]] static bool is_mouse_down(MouseButtons mouse_button);

    private:
        void key_down_actions(Uint8 const *current_key_state);

        void key_pressed_actions(Uint8 const *current_key_state);

        void key_up_actions(Uint8 const *current_key_state);

        void mouse_down_actions(Uint32 mouse_mask, int x_pos, int y_pos);

        void mouse_pressed_actions(Uint32 mouse_mask, int x_pos, int y_pos);

        void mouse_up_actions(Uint32 mouse_mask, int x_pos, int y_pos);

        std::vector<SDL_Scancode> m_keypressed;
        std::vector<Uint8> m_mousepressed;

        std::unordered_map<SDL_Scancode, Delegate<>> m_keydown_actions;
        std::unordered_map<SDL_Scancode, Delegate<>> m_keyup_actions;
        std::unordered_map<SDL_Scancode, Delegate<>> m_keypressed_actions;

        std::unordered_map<std::uint32_t, Delegate<int, int>>
                m_mouse_down_actions;
        std::unordered_map<std::uint32_t, Delegate<int, int>>
                m_mouse_pressed_actions;
        std::unordered_map<std::uint32_t, Delegate<int, int>>
                m_mouse_up_actions;
    };
} // namespace game
