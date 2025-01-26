//
// Created by Riebers on 26.01.2025.
//

#pragma once
#include <glm/vec2.hpp>

namespace component {
    struct RigidBody {
        glm::vec<2, float> velocity{};

        explicit RigidBody(glm::vec2 const &velocity = {}) : velocity{velocity} {
        }
    };
}
