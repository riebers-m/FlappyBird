//
// Created by riebers on 14.12.2024.
//

#pragma once
#include "Context.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include "common/Logger.hpp"
#include "resource/AssetStore.hpp"
#include "state/StateManager.hpp"

namespace game {
    class Game {
    private:
        LoggerPtr m_logger;
        Window m_window;
        Renderer m_renderer;
        Context m_context;
        AssetStore m_asset_store{};
        StateManager m_state_manager{};
        entt::registry m_registry{};
        bool m_running{false};

        void setup();

        void load_assets();

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
