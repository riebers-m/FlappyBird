//
// Created by Riebers on 14.02.2025.
//

#pragma once
#include <entt/entity/registry.hpp>

#include "BaseSystem.hpp"
#include "common/Logger.hpp"
#include "resource/AssetStore.hpp"

namespace systems {
    class RenderSystem : public BaseSystem {
    private:
        game::LoggerPtr m_logger;

    public:
        explicit RenderSystem(game::LoggerPtr logger, entt::registry &registry);

        void update(const game::Renderer &renderer, game::AssetStore &store) const;
    };
} // systems
