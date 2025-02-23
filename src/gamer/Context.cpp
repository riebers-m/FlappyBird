//
// Created by Riebers on 03.01.2025.
//
#include "Context.hpp"

namespace game {
    Context::Context(StateManager &state_manager, AssetStore &asset_store, entt::registry &registry, Renderer &renderer,
                     Window &window, systems::SystemsManager &systems_manager,
                     LoggerPtr logger, Game &game, Input &input) : state_manager(state_manager),
                                                                   asset_store(asset_store),
                                                                   registry(registry),
                                                                   renderer(renderer), window(window),
                                                                   systems_manager(systems_manager),
                                                                   logger(std::move(logger)), game{game}, input{input} {
    }
}
