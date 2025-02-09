//
// Created by riebers on 14.12.2024.
//

#pragma once
#include <chrono>
#include <SDL_pixels.h>
using namespace std::chrono_literals;

namespace game {
    std::chrono::nanoseconds constexpr timestep{20ms};
    std::chrono::nanoseconds constexpr render_time{5ms};

    SDL_Color constexpr BACKGROUND_COLOR = {43, 48, 54};
    SDL_Color constexpr BACKGROUND_ACCENT_COLOR = {12, 17, 20};

    SDL_Color constexpr PRIMARY_COLOR = {103, 0, 255};
    SDL_Color constexpr SECONDARY_COLOR = {138, 0, 255};
    SDL_Color constexpr ACCENT_COLOR = {183, 0, 255};
    SDL_Color constexpr TEXT_COLOR = {218, 0, 255};
    SDL_Color constexpr TEXT_COLOR_YELLOW = {253, 208, 23};
    SDL_Color constexpr TEXT_COLOR_WHITE = {255, 255, 255};
} // namespace game
