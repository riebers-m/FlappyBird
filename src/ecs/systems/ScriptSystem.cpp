//
// Created by Riebers on 25.01.2025.
//

#include "ScriptSystem.hpp"

namespace systems {
    ScriptSystem::ScriptSystem(game::LoggerPtr logger,
                               entt::registry &registry) :
        BaseSystem(registry), m_logger{logger}, m_script_engine() {}

    void ScriptSystem::load_script(std::filesystem::path const &script_file) {
        m_script_engine.load_from_file(script_file);
    }

    void ScriptSystem::setup() const { m_script_engine.setup(); }

    void ScriptSystem::update(std::chrono::milliseconds const &dt) const {
        m_script_engine.update(dt);
    }
    void ScriptSystem::publish_api() { m_script_engine.publish_vec2_api(); }
} // namespace systems
