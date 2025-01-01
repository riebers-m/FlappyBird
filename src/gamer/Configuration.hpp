//
// Created by riebers on 14.12.2024.
//

#pragma once
#include <cstdint>

namespace game {
    struct Configuration {
        std::uint16_t window_width{};
        std::uint16_t window_height{};
        float scale{};
    };
} // namespace game
