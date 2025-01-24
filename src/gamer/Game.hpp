//
// Created by riebers on 14.12.2024.
//

#pragma once
#include "Context.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include "common/Logger.hpp"
#include "resource/AudioManager.hpp"
#include "resource/FontManager.hpp"
#include "resource/TextureManager.hpp"
#include "state/StateManager.hpp"

namespace game {
    class Game {
    private:
        LoggerPtr m_logger;
        TextureManager m_texture_manager{};
        FontManager m_font_manager{};
        AudioManager m_audio_manager{};
        Window m_window;
        Renderer m_renderer;
        StateManager m_state_manager{};
        Registry m_registry{};
        Context m_context;
        bool m_running{false};
        Configuration m_config{};


        void setup();

        void handle_events();

        void update(Registry const &);

        // Registry interpolate(Registry const &current_state,
        //                      Registry const &previous_state, float dt);

        void render(Registry const &);

        explicit Game(LoggerPtr, Window, Renderer);

    public:
        Game() = delete;

        Game &operator=(Game const &) = delete;

        Game &operator=(Game &&) = delete;

        Game(Game const &) = delete;

        Game(Game &&) = delete;

        ~Game();

        void run();

        void stop();

        friend class Gamer;
    };
} // namespace game
