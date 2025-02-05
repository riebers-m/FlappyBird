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
    class TextureManager;
    class FontManager;
    class AudioManager;
    class Window;


    struct Context {
        explicit Context(StateManager &state_manager, AssetStore &asset_store,
                         TextureManager &texture_manager, FontManager &font_manager, AudioManager &audio_manager,
                         entt::registry &registry, Renderer &renderer, Window &window, LoggerPtr logger);

        StateManager &state_manager;
        AssetStore &asset_store;
        TextureManager &texture_manager;
        FontManager &font_manager;
        AudioManager &audio_manager;
        entt::registry &registry;
        Renderer &renderer;
        Window &window;
        LoggerPtr logger;
    };
}
