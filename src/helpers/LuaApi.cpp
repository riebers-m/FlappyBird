//
// Created by max on 09.03.25.
//

#include "LuaApi.hpp"
#include "glm/vec2.hpp"

namespace game {
    void LuaApi::publish_vec2(sol::state &lua) {
        lua.new_usertype<glm::vec2>(
                "Vec2",
                sol::constructors<glm::vec2(float, float), glm::vec2()>(), "x",
                &glm::vec2::x, "y", &glm::vec2::y);
    }
} // namespace game
