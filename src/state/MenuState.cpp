//
// Created by riebers on 14.12.2024.
//

#include "MenuState.hpp"
#include <utility>
#include "common/Button.hpp"
#include "common/Const.hpp"
#include "gamer/Renderer.hpp"


namespace game {
    MenuState::MenuState(Context context, std::function<void()> on_quit) : m_context(context),
                                                                           m_buttons(),
                                                                           m_text(),
                                                                           m_on_quit(std::move(on_quit)), m_input() {
        // auto heading = std::make_unique<Text>(m_context.renderer.get(), m_context.font_manager, "Flappy Bird",
        //                                       SDL_Rect{
        //                                           (static_cast<int>(m_context.window.size().width) / 2),
        //                                           static_cast<int>(m_context.window.size().height * 0.2), 0, 0
        //                                       }, TEXT_COLOR_YELLOW, asset_id::pico8_font_50);
        //
        // auto pos_heading = heading->get_rect();
        // pos_heading.x = pos_heading.x - pos_heading.w / 2;
        // heading->set_position({pos_heading.x, pos_heading.y});
        // m_text = std::move(heading);
        //
        //
        // auto play_button = std::make_unique<Button>(m_context, SDL_Rect{}, "Play", [&] {
        //     m_context.logger->info("Play");
        // });
        //
        // auto play_button_rect = play_button->size();
        // play_button_rect.x = (m_context.window.size().width / 2) - play_button_rect.w / 2;
        // play_button_rect.y = pos_heading.y + play_button_rect.h * 4;
        //
        // play_button->set_bbox(play_button_rect);
        // m_buttons.push_back(std::move(play_button));
        //
        // auto leaderboard_button = std::make_unique<Button>(
        //     m_context, SDL_Rect{}, "Leaderboard",
        //     [&] {
        //         m_context.logger->info("Leaderboard");
        //     });
        // auto leaderboard_button_rect = leaderboard_button->size();
        // leaderboard_button_rect.x = (m_context.window.size().width / 2) - leaderboard_button_rect.w / 2;
        // leaderboard_button_rect.y = play_button_rect.y + leaderboard_button_rect.h * 2;
        // leaderboard_button->set_bbox(leaderboard_button_rect);
        // m_buttons.push_back(std::move(leaderboard_button));
        //
        // auto quit_button = std::make_unique<Button>(
        //     m_context, SDL_Rect{}, "Quit",
        //     [&] { m_on_quit(); });
        //
        // auto quit_button_rect = quit_button->size();
        // quit_button_rect.x = (m_context.window.size().width / 2) - quit_button_rect.w / 2;
        // quit_button_rect.y = leaderboard_button_rect.y + quit_button_rect.h * 2;
        // quit_button->set_bbox(quit_button_rect);
        // m_buttons.push_back(std::move(quit_button));
        m_input.bind_keydown(SDL_Scancode::SDL_SCANCODE_Q, []() { return true; }, [this] {
            m_context.logger->debug("q key pressed");
        });

        m_input.bind_keypressed(SDL_SCANCODE_W, [this] { return true; }, [this] {
            m_rect.y -= 5;
        });
        m_input.bind_keypressed(SDL_SCANCODE_S, [this] { return true; }, [this] {
            m_rect.y += 5;
        });
        m_input.bind_keypressed(SDL_SCANCODE_A, [this] { return true; }, [this] {
            m_rect.x -= 5;
        });
        m_input.bind_keypressed(SDL_SCANCODE_D, [this] { return true; }, [this] {
            m_rect.x += 5;
        });
        m_input.bind_keyup(SDL_SCANCODE_E, [] { return true; }, [this] {
            m_context.logger->debug("e key pressed");
        });

        m_input.bind_mouse_down(MouseButtons::left, [] { return true; }, [this](int x, int y) {
            m_context.logger->debug(std::format("left mouse down: {},{}", x, y));
        });
        m_input.bind_mouse_up(MouseButtons::middle, [] { return true; }, [this](int x, int y) {
            m_context.logger->debug(std::format("middle mouse up: {},{}", x, y));
        });
        m_input.bind_mouse_pressed(MouseButtons::right, [] { return true; }, [this](int x, int y) {
            m_context.logger->debug(std::format("right mouse pressed: {},{}", x, y));
        });
        m_input.bind_mouse_pressed(MouseButtons::left, [] { return true; }, [this](int x, int y) {
            if (Input::is_key_down(SDL_SCANCODE_LCTRL)) {
                m_context.logger->debug(std::format("left mouse + LCTRL pressed: {},{}", x, y));
            }
        });

        m_rect.h = 200;
        m_rect.w = 200;
        m_rect.y = 300;
        m_rect.x = 300;
    }

    void MenuState::enter() {
        // auto const music = m_context.audio_manager.get_music(asset_id::menu_music);
        // if (Mix_PlayMusic(music.get(), -1) != 0) {
        //     throw std::runtime_error(std::format("Failed to play menu music: {}", Mix_GetError()));
        // }
    }

    void MenuState::exit() {
        // Mix_HaltMusic();
    }

    void MenuState::handle_events(SDL_Event const &event) {
        // for (auto &button: m_buttons) {
        //     button->handle_events(event);
        // }
    }

    void MenuState::update(entt::registry const &, const std::chrono::milliseconds &dt) {
        m_input.update();
        // for (auto &button: m_buttons) {
        //     if (button) {
        //         button->update();
        //     }
        // }
    }

    void MenuState::render(entt::registry const &) {
        if (auto const &texture = m_context.asset_store.get_texture("board"); texture.has_texture()) {
            SDL_RenderCopy(m_context.renderer.get(), texture.get().value(), nullptr, &m_rect);
        }

        // m_text->render();
        // for (auto &button: m_buttons) {
        //     button->render(m_context.renderer.get());
        // }
    }
} // namespace game
