//
// Created by riebers on 14.12.2024.
//

#include "DefaultState.hpp"
#include "common/Button.hpp"
#include "common/Const.hpp"
#include "../gamer/Input.hpp"
#include "ecs/systems/RenderSystem.hpp"
#include "ecs/systems/ScriptSystem.hpp"
#include "ecs/systems/SystemsManager.hpp"

namespace game {
    DefaultState::DefaultState(Context &context) : m_context(context) {
    }

    void DefaultState::enter() {
    }

    void DefaultState::exit() {
    }

    void DefaultState::handle_events(SDL_Event const &event) {
    }

    void DefaultState::update(entt::registry const &, const std::chrono::milliseconds &dt) {
        m_context.input.update();
        m_context.systems_manager.get_system<systems::ScriptSystem>().update(dt);
    }

    void DefaultState::render(entt::registry const &) {
        m_context.systems_manager.get_system<systems::RenderSystem>().update(m_context.renderer, m_context.asset_store);
    }
} // namespace game
