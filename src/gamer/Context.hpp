//
// Created by Riebers on 29.12.2024.
//

#pragma once
#include "common/Logger.hpp"
#include "ecs/Entity.hpp"
#include "resource/AssetStore.hpp"

namespace game {
    class Renderer;
    class StateManager;
    class AssetStore;
    class Window;


    struct Context {
        explicit Context(StateManager &state_manager, AssetStore &asset_store,
                         entt::registry &registry, Renderer &renderer, Window &window, LoggerPtr logger);

        StateManager &state_manager;
        AssetStore &asset_store;
        entt::registry &registry;
        Renderer &renderer;
        Window &window;
        LoggerPtr logger;
    };
}
