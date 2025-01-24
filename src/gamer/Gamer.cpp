//
// Created by HP on 14.12.2024.
//

#include "Gamer.hpp"

#include <SDL_image.h>
#include <stdexcept>
#include "Configuration.hpp"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

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

    Game Gamer::create_game(LoggerPtr logger, Gamer const &) {
        SDL_DisplayMode display_mode;
        if (SDL_GetCurrentDisplayMode(0, &display_mode) < 0) {
            throw std::runtime_error(std::format(
                "could not get display mode: {}", SDL_GetError()));
        }

        auto window = Window{
            "2d Game Engine",
            WindowSize{static_cast<std::uint32_t>(display_mode.w * 0.8), static_cast<uint32_t>(display_mode.h * 3 / 4)},
            WindowFlags::Borderless
        };
        auto renderer = Renderer{window, RendererFlags::Accelerate};
        renderer.set_renderer_blend_mode();

        return Game{std::move(logger), std::move(window), std::move(renderer)};
    }
} // namespace game
