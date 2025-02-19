//
// Created by Riebers on 24.01.2025.
//

#pragma once
#include <glm/vec2.hpp>

namespace component {
    using degree = float;

    struct Transform {
        glm::vec2 position{};
        degree rotation{};
        glm::vec2 scale{};

        explicit Transform(glm::vec2 const &position = {}, degree rotation = {},
                           glm::vec2 const &scale = {1.0, 1.0}) : position{position}, rotation{rotation},
                                                                  scale{scale} {
        }
    };
}
