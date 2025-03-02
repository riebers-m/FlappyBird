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

            if (!m_lua["setup"].valid() || !m_lua["update"].valid()) {
                throw std::runtime_error{std::format("Function setup or update not present in {}", path)};
            }

            m_lua["setup"]();
        } catch (sol::error const &e) {
            throw std::runtime_error{std::format("Could not load lua script {}: {}", path, e.what())};
        }
    }
} // game
