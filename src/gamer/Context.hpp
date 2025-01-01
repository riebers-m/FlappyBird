//
// Created by Riebers on 29.12.2024.
//

#pragma once
#include "resource/FontManager.hpp"
#include "resource/TextureManager.hpp"
#include "resource/AudioManager.hpp"
#include "state/StateManager.hpp"

namespace game {


    struct Context {
        Configuration config;
        std::shared_ptr<StateManager> state_manager;
        std::shared_ptr<TextureManager> texture_manager;
        std::shared_ptr<FontManager> font_manager;
        std::shared_ptr<AudioManager> audio_manager;
        SDL_Renderer *renderer;
        LoggerPtr logger;
        Registry registry;
    };

    using ContextPtr = std::shared_ptr<Context>;
}
