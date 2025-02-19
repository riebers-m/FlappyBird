//
// Created by Riebers on 18.02.2025.
//

#pragma once
#include <chrono>
#include <entt/entity/registry.hpp>

#include "BaseSystem.hpp"
#include "common/Logger.hpp"

namespace game {
    class Window;
}

namespace systems {
    class MovementSystem : public BaseSystem {
    private:
        game::LoggerPtr m_logger;

    public:
        explicit MovementSystem(game::LoggerPtr logger, entt::registry &registry);

        void update(game::Window const &world, std::chrono::milliseconds const &dt) const;
    };
} // systems
