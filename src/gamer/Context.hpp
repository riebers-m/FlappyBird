//
// Created by Riebers on 29.12.2024.
//

#pragma once
#include "common/Logger.hpp"
#include "ecs/Entity.hpp"
#include "resource/AssetStore.hpp"

namespace systems {
    class SystemsManager;
}

namespace game {
    class Renderer;
    class StateManager;
    class AssetStore;
    class Window;
    class Game;
    class Input;

    struct Context {
        explicit Context(StateManager &state_manager, AssetStore &asset_store,
                         entt::registry &registry, Renderer &renderer, Window &window,
                         systems::SystemsManager &systems_manager, LoggerPtr logger, Game &game, Input &input);

        StateManager &state_manager;
        AssetStore &asset_store;
        entt::registry &registry;
        Renderer &renderer;
        Window &window;
        systems::SystemsManager &systems_manager;
        LoggerPtr logger;
        Game &game;
        Input &input;
    };
}
