//
// Created by HP on 28.12.2024.
//

#include "Drawer.hpp"

#include "Const.hpp"
#include "Text.hpp"

namespace game {
    void Drawer::draw_filled_circle(SDL_Renderer *renderer, int centerX, int centerY, int32_t radius) {
        const auto squaredRadius = radius * radius;
        const int32_t minX = -radius;
        const int32_t minY = -radius;
        const auto maxX = radius;
        const auto maxY = radius;

        for (int y = minY; y <= maxY; ++y) {
            for (int x = minX; x <= maxX; ++x) {
                const auto distanceSquared = x * x + y * y;
                if (distanceSquared <= squaredRadius) {
                    SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
                }
            }
        }
    }
} // game
