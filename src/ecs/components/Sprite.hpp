//
// Created by Riebers on 26.01.2025.
//

#pragma once
#include <SDL_rect.h>
#include <string>

namespace component {
    enum class render_settings {
        rect_whole,
        rect_section,
    };

    struct Sprite {
        std::string id;
        SDL_Rect src_rect;
        render_settings render_setting{render_settings::rect_whole};

        explicit Sprite(std::string const &id = "", int width = 0, int height = 0, int x = 0, int y = 0,
                        render_settings render_setting = render_settings::rect_whole
        ) : id{id}, src_rect{.x = x, .y = y, .w = width, .h = height}, render_setting(render_setting) {
        }
    };
}
