//
// Created by riebers on 19.12.2024.
//

#include "resource/TextureManager.hpp"
#include "SDL_image.h"

namespace game {
    std::shared_ptr<SDL_Texture>
    TextureManager::load(SDL_Renderer *renderer,
                         std::filesystem::path const &path) const {
        if (SDL_Texture *texture = IMG_LoadTexture(renderer, path.string().c_str()); texture) {
            return {texture, [](SDL_Texture *texture) { SDL_DestroyTexture(texture); }};
        }
        throw std::runtime_error(std::format(
            "Could not load image form this path: {}", path.string()));
    }
} // namespace game
