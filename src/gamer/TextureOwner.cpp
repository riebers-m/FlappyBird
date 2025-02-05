//
// Created by Riebers on 26.01.2025.
//

#include "gamer/TextureOwner.hpp"
#include "Renderer.hpp"
#include <SDL_image.h>

namespace game {
    TextureOwner::TextureOwner(Renderer &renderer, std::filesystem::path const &path) : m_texture(std::nullopt) {
        load(renderer, path);
    }

    std::optional<SDL_Texture *> TextureOwner::get() const {
        if (m_texture.has_value()) {
            return {m_texture.value().get()};
        }
        return std::nullopt;
    }

    bool TextureOwner::has_texture() const {
        return m_texture.has_value();
    }

    void TextureOwner::load(const Renderer &renderer, std::filesystem::path const &path) {
        if (SDL_Texture *texture = IMG_LoadTexture(renderer.get(), path.string().c_str()); texture) {
            m_texture = {texture, SDL_DestroyTexture};
        } else {
            throw std::runtime_error(
                std::format("Could not load texture from path: {} ERROR: {}",
                            path.string(), SDL_GetError()));
        }
    }
} // game
