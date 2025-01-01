//
// Created by riebers on 14.12.2024.
//

#pragma once
#include <chrono>
#include <filesystem>
#include <SDL_pixels.h>
using namespace std::chrono_literals;

namespace game {
    std::chrono::nanoseconds constexpr timestep{20ms};
    std::chrono::nanoseconds constexpr render_time{5ms};

    std::filesystem::path const FONTS = "fonts";
    std::filesystem::path const IMAGES = "images";
    std::filesystem::path const SOUNDS = "sounds";
    std::filesystem::path const FONT_PICO = FONTS / "pico8.ttf";
    std::filesystem::path const BOARD_TEXTURE = IMAGES / "board.png";
    std::filesystem::path const COIN_ANIMATION = IMAGES / "coin-animation.png";
    std::filesystem::path const GAME_MUSIC = SOUNDS / "suits-you.mp3";
    std::filesystem::path const MENU_MUSIC = SOUNDS / "menu-music.mp3";
    std::filesystem::path const DRAW_SOUND = SOUNDS / "draw-sound.mp3";
    std::filesystem::path const CLICK_SOUND = SOUNDS / "retro-click.mp3";
    std::filesystem::path const LOSE_SOUND = SOUNDS / "8-bit-video-game-fail.mp3";
    std::filesystem::path const WIN_SOUND = SOUNDS / "8-bit-video-game-win-level.mp3";
    std::filesystem::path const READY_SOUND = SOUNDS / "ready-fight.mp3";

    SDL_Color constexpr BACKGROUND_COLOR = {43, 48, 54};
    SDL_Color constexpr BACKGROUND_ACCENT_COLOR = {12, 17, 20};

    SDL_Color constexpr PRIMARY_COLOR = {103, 0, 255};
    SDL_Color constexpr SECONDARY_COLOR = {138, 0, 255};
    SDL_Color constexpr ACCENT_COLOR = {183, 0, 255};
    SDL_Color constexpr TEXT_COLOR = {218, 0, 255};
    SDL_Color constexpr TEXT_COLOR_YELLOW = {253, 208, 23};
    SDL_Color constexpr TEXT_COLOR_WHITE = {255, 255, 255};
} // namespace game
