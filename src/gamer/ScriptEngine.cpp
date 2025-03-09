//
// Created by Riebers on 28.02.2025.
//

#include "ScriptEngine.hpp"
#include <format>
#include "helpers/LuaApi.hpp"

namespace game {
    ScriptEngine::ScriptEngine() : m_lua() {
        m_lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::package);
    }

    void ScriptEngine::load_from_file(std::filesystem::path const &path) {
        try {
            m_lua.script_file(path.string());
        } catch (sol::error const &e) {
            throw std::runtime_error{
                    std::format("Could not load lua script {}: {}",
                                path.string(), e.what())};
        }
    }

    void ScriptEngine::setup() const {
        if (m_lua["Setup"].valid()) {
            m_lua["Setup"]();
        }
    }

    void ScriptEngine::update(std::chrono::milliseconds const &dt) const {
        if (m_lua["Update"].valid()) {
            m_lua["Update"](dt.count());
        }
    }
    void ScriptEngine::publish_vec2_api() { LuaApi::publish_vec2(m_lua); }
} // namespace game
