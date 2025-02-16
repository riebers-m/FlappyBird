//
// Created by Riebers on 26.01.2025.
//

#pragma once
#include <glm/vec2.hpp>

namespace component {
    struct RigidBody {
        glm::ivec2 velocity{};

        explicit RigidBody(glm::ivec2 const &velocity = {}) : velocity{velocity} {
        }
    };
}
