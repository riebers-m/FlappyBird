//
// Created by riebers on 19.12.2024.
//

#pragma once
#include <SDL_render.h>
#include "ResourceManager.hpp"

namespace game {
    class TextureManager : public ResourceManager<TextureManager, SDL_Texture> {
    public:
        std::shared_ptr<SDL_Texture>
        load(SDL_Renderer *, std::filesystem::path const &path) const;
    };
} // namespace game
