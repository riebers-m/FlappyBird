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
#include "Texture.hpp"
#include "state/BaseState.hpp"
#include "state/MenuState.hpp"

namespace game {
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
    Game::Game(LoggerPtr logger, Window window, Renderer renderer) : m_logger(std::move(logger)),
                                                                     m_window{std::move(window)},
                                                                     m_renderer{std::move(renderer)},
                                                                     m_context{
                                                                         m_state_manager, m_texture_manager,
                                                                         m_font_manager, m_audio_manager,
                                                                         m_registry, m_renderer, m_window, m_logger
                                                                     }, m_running{true},
                                                                     m_texture(m_renderer, BOARD_TEXTURE) {
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

        entt::registry previous_board{};
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

    void Game::setup() {
#ifdef _DEBUG
        // Initialize IMGUI
        imgui_context = ImGui::CreateContext();
        ImGui_ImplSDL2_InitForSDLRenderer(m_window.get(), m_renderer.get());
        ImGui_ImplSDLRenderer2_Init(m_renderer.get());
#endif

        // m_texture.load(m_renderer, BOARD_TEXTURE);
        // Texture texture{m_renderer, BOARD_TEXTURE};
        if (!m_texture.has_texture()) {
            m_logger->warn("no texture loaded!");
        }
        // m_font_manager.load_resource(asset_id::pico8_font_10, FONT_PICO, 10);
        // m_font_manager.load_resource(asset_id::pico8_font_30, FONT_PICO, 30);
        // m_font_manager.load_resource(asset_id::pico8_font_50, FONT_PICO, 50);
        //
        // m_texture_manager.load_resource(asset_id::board_texture, m_renderer.get(), BOARD_TEXTURE);
        // m_texture_manager.load_resource(asset_id::coin_animation, m_renderer.get(), COIN_ANIMATION);
        //
        // m_audio_manager.load(AudioType::music, asset_id::game_music, GAME_MUSIC);
        // m_audio_manager.load(AudioType::music, asset_id::menu_music, MENU_MUSIC);
        // m_audio_manager.load(AudioType::chunk, asset_id::click_sound, CLICK_SOUND);
        // m_audio_manager.load(AudioType::chunk, asset_id::lose_sound, LOSE_SOUND);
        // m_audio_manager.load(AudioType::chunk, asset_id::win_sound, WIN_SOUND);
        // m_audio_manager.load(AudioType::chunk, asset_id::ready_sound, READY_SOUND);
        // m_audio_manager.load(AudioType::chunk, asset_id::draw_sound, DRAW_SOUND);

        m_state_manager.add_state(StateId::menu, std::make_unique<MenuState>(m_context, [&] { stop(); }));
    }

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
        // SDL_SetRenderDrawColor(m_renderer.get(), BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b,
        //                        BACKGROUND_COLOR.a);
        // SDL_RenderClear(m_renderer.get());
        if (m_texture.get().has_value()) {
            SDL_Rect dest{200, 200, 32, 32};
            SDL_RenderCopy(m_renderer.get(), m_texture.get().value(), NULL, &dest);
        }
        m_state_manager.render(state); {
#ifdef _DEBUG
            ImGuiRender imgui_renderer{
                m_renderer.get(), log_framrate,
                [logger = m_logger] { logger->draw("Logger"); }
            };
#endif
        }

        SDL_RenderPresent(m_renderer.get());
    }
} // namespace game
