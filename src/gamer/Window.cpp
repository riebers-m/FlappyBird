//
// Created by Riebers on 02.01.2025.
//

#include "Window.hpp"

#include <format>
#include <stdexcept>

namespace game {
    Window::Window(std::string const &title, WindowSize const &size,
                   WindowFlags flags) :
        m_window(std::unique_ptr<SDL_Window, WindowDeleter>(
                SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED,
                                 static_cast<int>(size.width),
                                 static_cast<int>(size.height), flags),
                [](SDL_Window *window) { SDL_DestroyWindow(window); })),
        m_size(size) {
        if (m_window == nullptr) {
            throw std::runtime_error(std::format(
                    "Failed to initialize window: {}", SDL_GetError()));
        }
        pos();
    }

    SDL_Window *Window::get() const { return m_window.get(); }

    bool Window::is_fullscreen() const {
        return SDL_GetWindowFlags(m_window.get()) == SDL_WINDOW_FULLSCREEN;
    }

    bool Window::is_shown() const {
        return SDL_GetWindowFlags(m_window.get()) == SDL_WINDOW_SHOWN;
    }

    bool Window::is_hidden() const {
        return SDL_GetWindowFlags(m_window.get()) == SDL_WINDOW_HIDDEN;
    }

    bool Window::is_borderless() const {
        return SDL_GetWindowFlags(m_window.get()) == SDL_WINDOW_BORDERLESS;
    }

    bool Window::is_input_focus() const {
        return SDL_GetWindowFlags(m_window.get()) == SDL_WINDOW_INPUT_FOCUS;
    }

    bool Window::is_always_on_top() const {
        return SDL_GetWindowFlags(m_window.get()) == SDL_WINDOW_ALWAYS_ON_TOP;
    }

    WindowPosition Window::pos() {
        WindowPosition pos;
        SDL_GetWindowPosition(m_window.get(), &pos.x, &pos.y);
        m_position = pos;
        return m_position;
    }

    void Window::set_pos(WindowPosition const &pos) {
        SDL_SetWindowPosition(m_window.get(), pos.x, pos.y);
        m_position = pos;
    }

    WindowSize Window::size() const { return m_size; }
} // namespace game
