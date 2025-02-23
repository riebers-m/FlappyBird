//
// Created by HP on 14.12.2024.
//

#include "Gamer.hpp"

#include <SDL_image.h>
#include <stdexcept>
#include "EngineConfiguration.hpp"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "helpers/FileReader.hpp"

namespace game {
    Gamer::Gamer() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            throw std::runtime_error{
                std::format("Init SDL failed: {}", SDL_GetError())
            };
        }
        if (TTF_Init() != 0) {
            throw std::runtime_error{
                std::format("Init TTF failed: {}", TTF_GetError())
            };
        }
        // Initialize PNG loading
        if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
            throw std::runtime_error{
                std::format("SDL_image could not initialize! SDL_image Error: {}", IMG_GetError())
            };
        }
        int const flags = MIX_INIT_MP3;
        if (auto result = Mix_Init(flags); result != flags) {
            throw std::runtime_error(std::format("SDL_mixer could not initialize! SDL_mixer Error: {}",
                                                 Mix_GetError()));
        }
        //Initialize SDL_mixer
        // To load mp3: https://gist.github.com/cdave1/10563386
        if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640) != 0) {
            throw std::runtime_error(std::format("SDL_mixer could not initialize! SDL_mixer Error: {}",
                                                 Mix_GetError()));
        }
    }

    Gamer::~Gamer() {
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        SDL_Quit();
    }

    Gamer const &Gamer::instance() {
        static Gamer gamer;
        return gamer;
    }

    // EngineConfiguration Gamer::load_config() {
    //     EngineConfiguration config;
    //     FileReader::read_file("nanoengine.config.json")
    //             .map([&config](std::string const &content) -> EngineConfiguration {
    //                 if (auto const result = json::deserialize_type(content, config);
    //                     result.error != json::Error::ok) {
    //                     throw std::runtime_error{"Could not deserialize nanoengine.config.json"};
    //                 }
    //                 return config;
    //             }).or_else([](std::string const &err) {
    //                 throw std::runtime_error(err);
    //             });;
    //     return config;
    // }

    // Game Gamer::create_game(LoggerPtr logger, Gamer const &) {
    //     logger->info("reading nanoengine.config.json");
    //     auto const config = Gamer::load_config();
    //
    //     WindowSize window_size{};
    //     if (config.displayMode) {
    //         logger->info(std::format("setting displayMode with aspectRatio: w:{}, h:{}", config.aspectRationWidth,
    //                                  config.aspectRationHeight));
    //         SDL_DisplayMode display_mode;
    //         if (SDL_GetCurrentDisplayMode(0, &display_mode) < 0) {
    //             throw std::runtime_error(std::format(
    //                 "could not get display mode: {}", SDL_GetError()));
    //         }
    //         window_size.width = static_cast<std::uint32_t>(display_mode.w * config.aspectRationWidth);
    //         window_size.height = static_cast<std::uint32_t>(display_mode.h * config.aspectRationHeight);
    //     } else {
    //         logger->info(std::format("setting width/height to: w:{}, h:{}", config.gameResolutionWidth,
    //                                  config.gameResolutionHeight));
    //         window_size.width = config.gameResolutionWidth;
    //         window_size.height = config.gameResolutionHeight;
    //     }
    //
    //     WindowFlags window_flags{WindowFlags::Borderless};
    //     if (config.gameFullscreen) {
    //         logger->info("setting Fullscreen");
    //         window_flags = WindowFlags::Fullscreen;
    //     }
    //
    //     auto window = Window{
    //         config.title,
    //         window_size,
    //         window_flags
    //     };
    //     auto renderer = Renderer{window, RendererFlags::Accelerate};
    //     renderer.set_renderer_blend_mode();
    //
    //     return Game{
    //         std::move(logger),
    //         std::move(window),
    //         std::move(renderer),
    //         config.assetDirectory / "assets.json"
    //     };
    // }

    std::pair<Window, Renderer> Gamer::load_config_from_file(LoggerPtr logger) {
        logger->info("reading nanoengine.config.json");
        auto const config = load_config();

        WindowSize window_size{};
        if (config.displayMode) {
            logger->info(std::format("setting displayMode with aspectRatio: w:{}, h:{}", config.aspectRationWidth,
                                     config.aspectRationHeight));
            SDL_DisplayMode display_mode;
            if (SDL_GetCurrentDisplayMode(0, &display_mode) < 0) {
                throw std::runtime_error(std::format(
                    "could not get display mode: {}", SDL_GetError()));
            }
            window_size.width = static_cast<std::uint32_t>(display_mode.w * config.aspectRationWidth);
            window_size.height = static_cast<std::uint32_t>(display_mode.h * config.aspectRationHeight);
        } else {
            logger->info(std::format("setting width/height to w:{}, h:{}", config.gameResolutionWidth,
                                     config.gameResolutionHeight));
            window_size.width = config.gameResolutionWidth;
            window_size.height = config.gameResolutionHeight;
        }

        WindowFlags window_flags{WindowFlags::Borderless};
        if (config.gameFullscreen) {
            logger->info("setting Fullscreen");
            window_flags = WindowFlags::Fullscreen;
        }

        auto window = Window{
            config.title,
            window_size,
            window_flags
        };
        auto renderer = Renderer{window, RendererFlags::Accelerate};
        renderer.set_renderer_blend_mode();
        return std::make_pair(std::move(window), std::move(renderer));
    }

    std::pair<Window, Renderer> Gamer::create_window_renderer_from_args(LoggerPtr logger, Args const &args) {
        logger->info("creating window and renderer from args");
        logger->info(std::format("setting width/height to w:{}, h:{}", args.window_size.width,
                                 args.window_size.height));
        auto window = Window{
            args.title,
            args.window_size,
            args.window_flags
        };
        auto renderer = Renderer{window, args.renderer_flags};
        renderer.set_renderer_blend_mode();
        return std::make_pair(std::move(window), std::move(renderer));
    }

    std::pair<Window, Renderer> Gamer::create_window_and_renderer(LoggerPtr logger, config_metadata config_metadata,
                                                                  Args const &args,
                                                                  Gamer const &) {
        if (config_metadata == config_metadata::from_file) {
            return load_config_from_file(logger);
        }
        if (config_metadata == config_metadata::from_args) {
            return create_window_renderer_from_args(logger, args);
        }
        throw std::runtime_error{std::format("invalid config_metadata")};
    }
} // namespace game
