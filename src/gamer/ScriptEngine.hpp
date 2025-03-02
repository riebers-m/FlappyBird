//
// Created by Riebers on 28.02.2025.
//

#pragma once
#include <filesystem>
#include <sol/state.hpp>

namespace game {
    class ScriptEngine {
    private:
        sol::state m_lua;

    public:
        ScriptEngine();

        void load_from_file(std::filesystem::path const &path);
    };
} // game
