//
// Created by riebers on 14.12.2024.
//

#include "Game.hpp"

#include <thread>
#include <utility>
#include "Context.hpp"
#include "common/Const.hpp"

#ifdef DEBUG
#include "common/ImGuiLogDebugLog.hpp"
#include "helpers/ImGuiRender.hpp"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "imgui_internal.h"
#endif

#include "Gamer.hpp"
// #include "common/SpdLog.hpp"
// #include "ecs/components/RigidBody.hpp"
// #include "ecs/components/Sprite.hpp"
// #include "ecs/components/Transform.hpp"
// #include "state/BaseState.hpp"
#include "ecs/systems/MovementSystem.hpp"
#include "ecs/systems/RenderSystem.hpp"
#include "ecs/systems/ScriptSystem.hpp"
#include "ecs/systems/SystemsManager.hpp"
#include "resource/AssetContainer.hpp"
#include "resource/AssetStore.hpp"
#include "state/DefaultState.hpp"
#include "version/version.hpp"

namespace game {
    struct NanoEngineConfig {
        std::filesystem::path assetDirectory;
    };

    REGISTER_MEMBER(NanoEngineConfig, assetDirectory);

#ifdef DEBUG
    static void log_framrate() {
        ImGui::SetNextWindowBgAlpha(0.7f);
        if (ImGui::Begin("Frames per second", nullptr,
                         ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                        static_cast<double>(1000.0f / ImGui::GetIO().Framerate),
                        static_cast<double>(ImGui::GetIO().Framerate));
        }
        ImGui::End();
    }

    static ImGuiContext *imgui_context{nullptr};
#endif

    Game::Game() :
        m_context{m_state_manager, m_asset_store, m_registry,
                  m_renderer,      m_window,      m_systems_manager,
                  m_logger,        *this,         m_input},
        m_running{true} {
#ifdef DEBUG
        m_logger = std::make_shared<game::Logger>(
                std::make_unique<game::ImGuiLogWindow>());
#else
        m_logger = std::make_shared<game::Logger>(
                std::make_unique<game::Spdlogger>(spdlog::basic_logger_mt(
                        "connect4_logger", "logs/connect4-log.txt")));
#endif
        auto [window, renderer] = Gamer::create_window_and_renderer(
                m_logger, config_metadata::from_file);
        m_window = std::move(window);
        m_renderer = std::move(renderer);

        m_state_manager.add_state(StateId::menu,
                                  std::make_unique<DefaultState>(m_context));
#ifdef DEBUG
        // Initialize IMGUI
        imgui_context = ImGui::CreateContext();
        ImGui_ImplSDL2_InitForSDLRenderer(m_window.get(), m_renderer.get());
        ImGui_ImplSDLRenderer2_Init(m_renderer.get());
#endif

#ifdef DEBUG
        m_logger->info("Running Debug Build");
#else
        m_logger->info("Running Release Build");
#endif

        m_logger->info(version());
    }

    Game::~Game() {
#ifdef DEBUG
        if (imgui_context) {
            ImGui_ImplSDLRenderer2_Shutdown();
            ImGui_ImplSDL2_Shutdown();
            ImGui::DestroyContext();
        }
#endif
    }

    void Game::run() {
        register_systems();
        load_assets();
        load_scripts();

        setup();

        std::chrono::nanoseconds lag{0ns};
        using clock = std::chrono::high_resolution_clock;
        auto time_start = clock::now();
        auto last_render_time = time_start;

        while (m_running) {
            auto current_time = clock::now();
            auto frame_time = current_time - time_start;
            time_start = current_time;
            lag += std::chrono::duration_cast<std::chrono::nanoseconds>(
                    frame_time);

            handle_events();

            // update game logic as lag permits
            while (lag >= timestep) {
                lag -= timestep;
                // previous_board = m_board;
                update(m_registry);
            }

            if (current_time - last_render_time >= render_time) {
                // value between 0..1
                //                auto const alpha =
                //                        static_cast<float>(lag.count()) /
                //                        timestep.count();
                // auto const current_state =
                //         interpolate(m_board, previous_board, alpha);
                render(m_registry);
                last_render_time = current_time;
            }
            // Removes deleted states
            m_state_manager.process_states();
        }
    }

    void Game::register_systems() {
        m_systems_manager.add_system<systems::RenderSystem>(m_logger,
                                                            m_registry);
        m_systems_manager.add_system<systems::ScriptSystem>(m_logger,
                                                            m_registry);
    }

    void Game::load_assets() {
        auto const config = load_config();
        m_asset_store.load_from_file(config.assetDirectory, m_renderer);
    }

    void Game::load_scripts() {
        if (auto const script_path =
                    m_asset_store.get_script_path("nano-script-engine");
            script_path.has_value()) {
            auto &script_engine =
                    m_systems_manager.get_system<systems::ScriptSystem>();
            script_engine.publish_api();
            script_engine.load_script(script_path.value());
            script_engine.setup();
        }
    }

    void Game::handle_events() {
        SDL_Event event{};

        while (SDL_PollEvent(&event)) {
#ifdef DEBUG
            ImGui_ImplSDL2_ProcessEvent(&event);
#endif

            switch (event.type) {
                case SDL_QUIT:
                    m_running = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        m_running = false;
                    }
                default:;
            }
            m_state_manager.handle_events(event);
        }
    }

    void Game::update(entt::registry const &state) {
        m_state_manager.update(
                state, std::chrono::duration_cast<std::chrono::milliseconds>(
                               timestep));
    }

    // Registry interpolate(Registry const &current_state,
    //                      Registry const &previous_state, float dt) {
    //     return current_state;
    // }

    void Game::render(entt::registry const &state) {
        m_renderer.set_draw_color(BACKGROUND_COLOR);
        m_renderer.clear();

        m_state_manager.render(state);
#ifdef DEBUG
        {
            ImGuiRender imgui_renderer{
                    m_renderer.get(), log_framrate,
                    [logger = m_logger] { logger->draw("Logger"); }};
        }
#endif


        SDL_RenderPresent(m_renderer.get());
    }

    void Game::stop() { m_running = false; }
} // namespace game
