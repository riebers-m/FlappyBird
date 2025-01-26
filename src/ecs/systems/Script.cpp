//
// Created by Riebers on 25.01.2025.
//

#include "Script.hpp"

namespace systems {
    Script::Script(std::unique_ptr<sol::state> lua) : m_lua(std::move(lua)) {
    }
} // system
