//
// Created by riebers on 14.12.2024.
//

#include "Game.hpp"

#include <thread>
#include <utility>
#include "Context.hpp"
#include "common/Const.hpp"

#ifdef _DEBUG
#include "helpers/ImGuiRender.hpp"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "imgui_internal.h"
#endif
#include "Gamer.hpp"
#include "common/ImGuiLogDebugLog.hpp"
#include "ecs/components/RigidBody.hpp"
#include "ecs/components/Sprite.hpp"
#include "ecs/components/Transform.hpp"
#include "ecs/systems/MovementSystem.hpp"
#include "ecs/systems/RenderSystem.hpp"
#include "ecs/systems/SystemsManager.hpp"
#include "resource/AssetContainer.hpp"
#include "resource/AssetStore.hpp"
#include "state/BaseState.hpp"
#include "state/DefaultState.hpp"
#include "version/version.hpp"

namespace game {
    struct NanoEngineConfig {
        std::filesystem::path assetDirectory;
    };

    REGISTER_MEMBER(NanoEngineConfig, assetDirectory);

#ifdef _DEBUG
    static void log_framrate() {
        ImGui::SetNextWindowBgAlpha(0.7);
        if (ImGui::Begin("Frames per second", nullptr,
                         ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                        1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
        }
        ImGui::End();
    }

    static ImGuiContext *imgui_context{nullptr};
#endif

    Game::Game() : m_context{
                       m_state_manager, m_asset_store,
                       m_registry, m_renderer, m_window,
                       m_systems_manager, m_logger, *this, m_input
                   },
                   m_running{true} {
#ifdef _DEBUG
        m_logger = std::make_shared<game::Logger>(
            std::make_unique<game::ImGuiLogWindow>());
#else
        m_logger = std::make_shared<game::Logger>(
            std::make_unique<game::Spdlogger>(spdlog::basic_logger_mt("connect4_logger", "logs/connect4-log.txt")
            )
        );
#endif
        auto [window, renderer] = Gamer::create_window_and_renderer(
            m_logger, config_metadata::from_file);
        m_window = std::move(window);
        m_renderer = std::move(renderer);

        m_systems_manager.add_system<systems::RenderSystem>(m_logger, m_registry);
        m_state_manager.add_state(StateId::menu, std::make_unique<DefaultState>(m_context));
#ifdef _DEBUG
        // Initialize IMGUI
        imgui_context = ImGui::CreateContext();
        ImGui_ImplSDL2_InitForSDLRenderer(m_window.get(), m_renderer.get());
        ImGui_ImplSDLRenderer2_Init(m_renderer.get());
#endif

#ifdef _DEBUG
        m_logger->info("Running Debug Build");
#else
        m_logger->info("Running Release Build");
#endif

        m_logger->info(version());
    }

    Game::~Game() {
#ifdef _DEBUG
        if (imgui_context) {
            ImGui_ImplSDLRenderer2_Shutdown();
            ImGui_ImplSDL2_Shutdown();
            ImGui::DestroyContext();
        }
#endif
    }

    void Game::run() {
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
                auto const alpha =
                        static_cast<float>(lag.count()) / timestep.count();
                // auto const current_state =
                //         interpolate(m_board, previous_board, alpha);
                render(m_registry);
                last_render_time = current_time;
            }
            // Removes deleted states
            m_state_manager.process_states();
        }
    }

    void Game::stop() {
        m_running = false;
    }

    // void Game::setup() { {
    //         auto entity = ecs::Entity::create(m_registry);
    //         entity.add_component<component::Sprite>("pong-sheet", 50, 110, 0, 20,
    //                                                 component::render_settings::rect_section);
    //         entity.add_component<component::Transform>(glm::vec2{200, 700});
    //         entity.add_component<component::RigidBody>(glm::vec2{0, 50});
    //     } {
    //         auto entity = ecs::Entity::create(m_registry);
    //         entity.add_component<component::Sprite>("pong-sheet", 50, 150, 50, 0,
    //                                                 component::render_settings::rect_section);
    //         entity.add_component<component::Transform>(glm::vec2{400, 200});
    //     }
    //     m_state_manager.add_state(StateId::menu, std::make_unique<DefaultState>(m_context));
    //
    //     m_systems_manager.add_system<systems::RenderSystem>(m_logger, m_registry);
    //     if (!m_systems_manager.has_system<systems::RenderSystem>()) {
    //         throw std::runtime_error("NO RENDERSYSTEM FOUND!");
    //     }
    // }

    void Game::handle_events() {
        SDL_Event event{};

        while (SDL_PollEvent(&event)) {
#ifdef _DEBUG
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
                default: ;
            }
            m_state_manager.handle_events(event);
        }
    }

    void Game::update(entt::registry const &state) {
        m_state_manager.update(
            state,
            std::chrono::duration_cast<std::chrono::milliseconds>(
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
#ifdef _DEBUG
        {
            ImGuiRender imgui_renderer{
                m_renderer.get(), log_framrate,
                [logger = m_logger] { logger->draw("Logger"); }
            };
        }
#endif


        SDL_RenderPresent(m_renderer.get());
    }
} // namespace game
