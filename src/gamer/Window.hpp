//
// Created by Riebers on 02.01.2025.
//

#pragma once
#include <functional>
#include <memory>
#include <string>
#include "SDL_video.h"
#include "glm/vec2.hpp"

struct SDL_Window;

namespace game {
    using WindowDeleter = std::function<void(SDL_Window *window)>;

    struct WindowSize {
        std::uint32_t width;
        std::uint32_t height;
    };

    using WindowPosition = glm::vec<2, int>;

    enum WindowFlags : std::uint32_t {
        Fullscreen = SDL_WINDOW_FULLSCREEN,
        Shown = SDL_WINDOW_SHOWN,
        Hidden = SDL_WINDOW_HIDDEN,
        Borderless = SDL_WINDOW_BORDERLESS,
        InputFocus = SDL_WINDOW_INPUT_FOCUS,
        AlwaysOnTop = SDL_WINDOW_ALWAYS_ON_TOP,
    };

    class Window {
    private:
        std::unique_ptr<SDL_Window, WindowDeleter> m_window;
        WindowSize m_size{};
        WindowPosition m_position{};

    public:
        explicit Window(std::string const &title, WindowSize const &size,
                        WindowFlags flags);

        Window() = default;

        [[nodiscard]] SDL_Window *get() const;

        [[nodiscard]] WindowSize size() const;

        [[nodiscard]] bool is_fullscreen() const;

        [[nodiscard]] bool is_shown() const;

        [[nodiscard]] bool is_hidden() const;

        [[nodiscard]] bool is_borderless() const;

        [[nodiscard]] bool is_input_focus() const;

        [[nodiscard]] bool is_always_on_top() const;

        WindowPosition pos();

        void set_pos(WindowPosition const &pos);
    };
} // namespace game
