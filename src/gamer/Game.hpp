//
// Created by riebers on 14.12.2024.
//

#pragma once
#include "Context.hpp"
#include "FontOwner.hpp"
#include "MusicOwner.hpp"
#include "Renderer.hpp"
#include "SoundOwner.hpp"
#include "Texture.hpp"
#include "Window.hpp"
#include "common/Logger.hpp"
#include "resource/AssetStore.hpp"
#include "resource/AudioManager.hpp"
#include "resource/FontManager.hpp"
#include "resource/TextureManager.hpp"
#include "state/StateManager.hpp"

namespace game {
    class Game {
    private:
        LoggerPtr m_logger;
        Window m_window;
        Renderer m_renderer;
        Context m_context;
        AssetStore m_asset_store{};
        TextureManager m_texture_manager{};
        FontManager m_font_manager{};
        AudioManager m_audio_manager{};
        StateManager m_state_manager{};
        entt::registry m_registry{};
        TextureOwner m_texture;
        FontOwner m_font;
        SoundOwner m_sound;
        MusicOwner m_music;
        bool m_running{false};

        void setup();

        void handle_events();

        void update(entt::registry const &);

        // Registry interpolate(Registry const &current_state,
        //                      Registry const &previous_state, float dt);

        void render(entt::registry const &);

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
