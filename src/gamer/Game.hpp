//
// Created by riebers on 14.12.2024.
//

#pragma once
#include "Context.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include "Input.hpp"
#include "ScriptEngine.hpp"
#include "common/Logger.hpp"
#include "ecs/systems/SystemsManager.hpp"
#include "resource/AssetStore.hpp"
#include "state/StateManager.hpp"

namespace game {
    class Game {
    protected:
        LoggerPtr m_logger;
        Window m_window;
        Renderer m_renderer;
        AssetStore m_asset_store{};
        StateManager m_state_manager{};
        entt::registry m_registry{};
        systems::SystemsManager m_systems_manager;
        Input m_input;
        Context m_context;
        bool m_running{false};
        ScriptEngine m_script_engine;

        virtual void setup() = 0;

        void handle_events();

        void update(entt::registry const &);

        // Registry interpolate(Registry const &current_state,
        //                      Registry const &previous_state, float dt);

        void render(entt::registry const &);

    public:
        Game();

        Game &operator=(Game const &) = delete;

        Game(Game const &) = delete;

        Game &operator=(Game &&) = delete;

        virtual ~Game();

        void run();

        void stop();
    };
} // namespace game
