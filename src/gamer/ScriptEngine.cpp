//
// Created by Riebers on 28.02.2025.
//

#include "ScriptEngine.hpp"

namespace game {
    ScriptEngine::ScriptEngine() : m_lua() {
        m_lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::package);
    }

    void ScriptEngine::load_from_file(std::filesystem::path const &path) {
        try {
            m_lua.script_file(path.string());
        } catch (sol::error const &e) {
            throw std::runtime_error{std::format("Could not load lua script {}: {}", path.string(), e.what())};
        }
    }

    void ScriptEngine::setup() const {
        if (m_lua["setup"].valid()) {
            m_lua["setup"]();
        }
    }

    void ScriptEngine::update(std::chrono::milliseconds const &dt) const {
        if (m_lua["update"].valid()) {
            m_lua["update"](dt.count());
        }
    }
} // game
