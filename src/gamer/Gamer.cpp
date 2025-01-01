//
// Created by HP on 14.12.2024.
//

#include "Gamer.hpp"

#include <format>
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

        auto const window_height = static_cast<uint16_t>(display_mode.h * 0.8);
        auto const window_width = static_cast<uint16_t>(window_height * 3 / 4);
        auto const scale = 1.0f;
        auto const config = Configuration{window_width, window_height, scale};

        SDL_Window *window =
                SDL_CreateWindow("2D Game Engine", SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED, config.window_width,
                                 config.window_height, SDL_WINDOW_BORDERLESS);
        if (window == nullptr) {
            throw std::runtime_error("could not create window.");
        }
        SDL_Renderer *renderer =
                SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr) {
            throw std::runtime_error("could not create renderer.");
        }
        if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND) != 0) {
            throw std::runtime_error{std::format("could not set blend mode: {}", SDL_GetError())};
        }
        return Game{std::move(logger), window, renderer, config};
    }
} // namespace game
