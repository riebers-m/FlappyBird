//
// Created by riebers on 14.12.2024.
//

#pragma once
#include <SDL_render.h>


#include "Context.hpp"
#include "common/Logger.hpp"
#include "resource/AudioManager.hpp"
#include "resource/FontManager.hpp"
#include "resource/TextureManager.hpp"
#include "state/StateManager.hpp"


namespace game {
    class Game {
    private:
        std::unique_ptr<SDL_Window, void (*)(SDL_Window *)> m_window;
        std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)> m_renderer;

        LoggerPtr m_logger;
        std::shared_ptr<TextureManager> m_texture_manager;
        std::shared_ptr<FontManager> m_font_manager;
        std::shared_ptr<AudioManager> m_audio_manager;
        bool m_running;
        Registry m_registry;
        std::shared_ptr<StateManager> m_state_manager;
        Configuration m_config{};


        void setup();

        void handle_events();

        void update(Registry const &);

        Registry interpolate(Registry const &current_state,
                              Registry const &previous_state, float dt);

        void render(Registry const &);

    public:
        explicit Game(LoggerPtr, SDL_Window *, SDL_Renderer *,
                      Configuration const &);

        ~Game();

        void run();

        void stop();
    };
} // namespace game
