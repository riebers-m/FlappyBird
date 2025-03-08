//
// Created by riebers on 14.12.2024.
//

#pragma once
#include "EngineConfiguration.hpp"
#include "common/Logger.hpp"
#include "gamer/Renderer.hpp"
#include "gamer/Window.hpp"

namespace game {
    enum class config_metadata {
        from_file,
        from_args,
    };

    class Gamer final {
    public:
        struct Args {
            explicit Args(
                    std::string const &title = "nanoengine2d",
                    WindowSize window_size = {.width = 800, .height = 600},
                    WindowFlags window_flags = WindowFlags::Borderless,
                    RendererFlags renderer_flags = RendererFlags::Accelerate,
                    std::filesystem::path const &asset_directory =
                            {"assets.json"}) :
                title{title}, window_size{window_size},
                window_flags{window_flags}, renderer_flags{renderer_flags},
                asset_directory{asset_directory} {}
            std::string title;
            WindowSize window_size;
            WindowFlags window_flags;
            RendererFlags renderer_flags;
            std::filesystem::path asset_directory;
        };

    private:
        Gamer();

        ~Gamer();

        static Gamer const &instance();


        static std::pair<Window, Renderer>
        load_config_from_file(LoggerPtr logger);

        static std::pair<Window, Renderer>
        create_window_renderer_from_args(LoggerPtr logger, Args const &);

    public:
        // static EngineConfiguration load_config();

        Gamer(Gamer const &) = delete;

        Gamer(Gamer &&) = delete;

        Gamer &operator=(Gamer const &) = delete;

        Gamer &operator=(Gamer &&) = delete;

        // static Game create_game(LoggerPtr logger, );

        static std::pair<Window, Renderer> create_window_and_renderer(
                LoggerPtr logger,
                config_metadata config_metadata = config_metadata::from_args,
                Args const & = Args(), Gamer const & = instance());
    };
} // namespace game
