//
// Created by riebers on 14.12.2024.
//

#pragma once
#include "EngineConfiguration.hpp"
#include "gamer/Window.hpp"
#include "gamer/Renderer.hpp"
#include "common/Logger.hpp"

namespace game {
    enum class config_metadata {
        from_file,
        from_args,
    };

    class Gamer final {
    public:
        struct Args {
            std::string title{"Nanoengine"};
            WindowSize window_size{.width = 800, .height = 600};
            WindowFlags window_flags{WindowFlags::Borderless};
            RendererFlags renderer_flags{RendererFlags::Accelerate};
            std::filesystem::path asset_directory{"assets.json"};
        };

    private:
        Gamer();

        ~Gamer();

        static Gamer const &instance();


        static std::pair<Window, Renderer> load_config_from_file(LoggerPtr logger);

        static std::pair<Window, Renderer> create_window_renderer_from_args(LoggerPtr logger, Args const &);

    public:
        // static EngineConfiguration load_config();

        Gamer(Gamer const &) = delete;

        Gamer(Gamer &&) = delete;

        Gamer &operator=(Gamer const &) = delete;

        Gamer &operator=(Gamer &&) = delete;

        // static Game create_game(LoggerPtr logger, );

        static std::pair<Window, Renderer> create_window_and_renderer(LoggerPtr logger,
                                                                      config_metadata config_metadata =
                                                                              config_metadata::from_args,
                                                                      Args const & = Args{},
                                                                      Gamer const & = instance());
    };
} // game
