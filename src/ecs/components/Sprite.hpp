//
// Created by Riebers on 26.01.2025.
//

#pragma once
#include <SDL_rect.h>
#include <string>

namespace component {
    struct Sprite {
        std::string id;
        SDL_Rect src_rect;
        bool whole_rect{false};

        explicit Sprite(std::string const &id = "", int width = 0, int height = 0, int x = 0, int y = 0,
                        bool render_whole_rect = false
        ) : id{id}, src_rect{.x = x, .y = y, .w = width, .h = height}, whole_rect(render_whole_rect) {
        }
    };
}
