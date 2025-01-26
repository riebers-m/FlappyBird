//
// Created by Riebers on 25.01.2025.
//

#pragma once
#include <sol/sol.hpp>

namespace systems {
    class Script {
    private:
        std::unique_ptr<sol::state> m_lua;

    public:
        explicit Script(std::unique_ptr<sol::state> lua);
    };
} // system
