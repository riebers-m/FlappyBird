//
// Created by riebers on 14.12.2024.
//

#include "Game.hpp"

#include <thread>

#include "Context.hpp"
#include "common/Const.hpp"
#ifdef _DEBUG
#include "helpers/ImGuiRender.hpp"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "imgui_internal.h"
#endif
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

    Game::Game(LoggerPtr logger, SDL_Window *window, SDL_Renderer *renderer,
               Configuration const &config) : m_window(window, [](SDL_Window *w) { SDL_DestroyWindow(w); }),
                                              m_renderer(renderer, [](SDL_Renderer *r) { SDL_DestroyRenderer(r); }),
                                              m_logger{std::move(logger)},
                                              m_texture_manager(std::make_shared<TextureManager>()),
                                              m_font_manager(std::make_shared<FontManager>(m_logger)),
                                              m_audio_manager(std::make_shared<AudioManager>()),
                                              m_running{true}, m_registry(std::make_shared<entt::registry>()),
                                              m_state_manager(std::make_shared<StateManager>(config)),
                                              m_config(config) {
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

        Registry previous_board{};
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
            m_state_manager->process_states();
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

        ContextPtr context = std::make_shared<Context>(m_config, m_state_manager, m_texture_manager, m_font_manager,
                                                       m_audio_manager,
                                                       m_renderer.get(), m_logger, m_registry);

        m_font_manager->load_resource(asset_id::pico8_font_10, FONT_PICO, 10);
        m_font_manager->load_resource(asset_id::pico8_font_30, FONT_PICO, 30);
        m_font_manager->load_resource(asset_id::pico8_font_50, FONT_PICO, 50);

        m_texture_manager->load_resource(asset_id::board_texture, m_renderer.get(), BOARD_TEXTURE);
        m_texture_manager->load_resource(asset_id::coin_animation, m_renderer.get(), COIN_ANIMATION);

        m_audio_manager->load(AudioType::music, asset_id::game_music, GAME_MUSIC);
        m_audio_manager->load(AudioType::music, asset_id::menu_music, MENU_MUSIC);
        m_audio_manager->load(AudioType::chunk, asset_id::click_sound, CLICK_SOUND);
        m_audio_manager->load(AudioType::chunk, asset_id::lose_sound, LOSE_SOUND);
        m_audio_manager->load(AudioType::chunk, asset_id::win_sound, WIN_SOUND);
        m_audio_manager->load(AudioType::chunk, asset_id::ready_sound, READY_SOUND);
        m_audio_manager->load(AudioType::chunk, asset_id::draw_sound, DRAW_SOUND);

        m_state_manager->add_state(StateId::menu, std::make_unique<MenuState>(context, [&] { stop(); }));

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
            m_state_manager->handle_events(event);
        }
    }

    void Game::update(Registry const& state) {
        m_state_manager->update(
            state,
            std::chrono::duration_cast<std::chrono::milliseconds>(
                timestep));
    }

    Registry interpolate(Registry const &current_state,
                              Registry const &previous_state, float dt) {
        return current_state;
    }

    void Game::render(Registry const &state) {
        SDL_SetRenderDrawColor(m_renderer.get(), BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b,
                               BACKGROUND_COLOR.a);
        SDL_RenderClear(m_renderer.get());

        m_state_manager->render(state); {
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
