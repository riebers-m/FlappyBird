//
// Created by HP on 28.12.2024.
//

#pragma once
#include "gamer/Context.hpp"


namespace game {
    class Drawer {
    public:
        static void draw_filled_circle(SDL_Renderer *renderer, int centerX,
                                       int centerY, int32_t radius);
    };
} // game
