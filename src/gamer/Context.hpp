//
// Created by Riebers on 29.12.2024.
//

#pragma once
#include "common/Logger.hpp"
#include "ecs/Entity.hpp"

namespace game {
    class Renderer;
    class StateManager;
    class TextureManager;
    class FontManager;
    class AudioManager;
    class Window;


    struct Context {
        explicit Context(StateManager &state_manager,
                         TextureManager &texture_manager, FontManager &font_manager, AudioManager &audio_manager,
                         entt::registry &registry, Renderer &renderer, Window &window, LoggerPtr logger);

        StateManager &state_manager;
        TextureManager &texture_manager;
        FontManager &font_manager;
        AudioManager &audio_manager;
        entt::registry &registry;
        Renderer &renderer;
        Window &window;
        LoggerPtr logger;
    };
}
