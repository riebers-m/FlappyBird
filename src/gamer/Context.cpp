//
// Created by Riebers on 03.01.2025.
//
#include "Context.hpp"

namespace game {
    Context::Context(StateManager &state_manager, AssetStore &asset_store, entt::registry &registry, Renderer &renderer,
                     Window &window, systems::RenderSystem &render_system,
                     LoggerPtr logger) : state_manager(state_manager), asset_store(asset_store),
                                         registry(registry),
                                         renderer(renderer), window(window), render_system(render_system),
                                         logger(std::move(logger)) {
    }
}
