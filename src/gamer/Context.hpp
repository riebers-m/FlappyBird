//
// Created by Riebers on 29.12.2024.
//

#pragma once
#include "Registry.hpp"
#include "common/Logger.hpp"

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
                         Registry &registry, Renderer &renderer, Window &window, LoggerPtr logger);

        StateManager &state_manager;
        TextureManager &texture_manager;
        FontManager &font_manager;
        AudioManager &audio_manager;
        Registry &registry;
        Renderer &renderer;
        Window &window;
        LoggerPtr logger;
    };
}
