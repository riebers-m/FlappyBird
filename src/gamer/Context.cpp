//
// Created by Riebers on 03.01.2025.
//
#include "Context.hpp"

namespace game {
    Context::Context(StateManager &state_manager, AssetStore &asset_store, entt::registry &registry, Renderer &renderer,
                     Window &window, LoggerPtr logger) : state_manager(state_manager), asset_store(asset_store),
                                                         registry(registry),
                                                         renderer(renderer), window(window), logger(std::move(logger)) {
    }
}
