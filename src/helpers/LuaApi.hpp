//
// Created by max on 09.03.25.
//

#pragma once
#include <sol/state.hpp>
namespace game {
    class LuaApi {
    public:
        static void publish_vec2(sol::state &lua);
    };

} // namespace game
