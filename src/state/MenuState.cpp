//
// Created by riebers on 14.12.2024.
//

#include "MenuState.hpp"
#include <utility>
#include "common/Button.hpp"
#include "common/Const.hpp"
#include "ecs/systems/MovementSystem.hpp"
#include "ecs/systems/RenderSystem.hpp"
#include "ecs/systems/SystemsManager.hpp"
#include "gamer/Renderer.hpp"


namespace game {
    MenuState::MenuState(Context &context, std::function<void()> on_quit) : m_context(context),
                                                                            m_buttons(),
                                                                            m_text(),
                                                                            m_on_quit(std::move(on_quit)), m_input() {
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
        m_context.systems_manager.get_system<systems::MovementSystem>().update(m_context.window, dt);
        // for (auto &button: m_buttons) {
        //     if (button) {
        //         button->update();
        //     }
        // }
    }

    void MenuState::render(entt::registry const &) {
        m_context.systems_manager.get_system<systems::RenderSystem>().update(m_context.renderer, m_context.asset_store);


        // m_text->render();
        // for (auto &button: m_buttons) {
        //     button->render(m_context.renderer.get());
        // }
    }
} // namespace game
