//
// Created by Riebers on 25.01.2025.
//

#pragma once
#include <entt/entity/registry.hpp>

#include "BaseSystem.hpp"
#include "common/Logger.hpp"
#include "gamer/ScriptEngine.hpp"

namespace systems {
    class ScriptSystem : public BaseSystem {
    private:
        game::LoggerPtr m_logger;
        game::ScriptEngine m_script_engine;

    public:
        explicit ScriptSystem(game::LoggerPtr logger, entt::registry &registry);

        void load_script(std::filesystem::path const &script_file);

        void setup() const;

        void update(std::chrono::milliseconds const &dt) const;
    };
} // system
