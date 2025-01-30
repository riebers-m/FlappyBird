//
// Created by Riebers on 26.01.2025.
//

#include "Texture.hpp"
#include "Renderer.hpp"
#include <SDL_image.h>

namespace game {
    Texture::Texture(Renderer &renderer, std::filesystem::path const &path) : m_texture(std::nullopt) {
        load(renderer, path);
    }

    std::optional<SDL_Texture *> Texture::get() const {
        if (m_texture.has_value()) {
            return {m_texture.value().get()};
        }
        return std::nullopt;
    }

    bool Texture::has_texture() const {
        return m_texture.has_value();
    }

    void Texture::load(const Renderer &renderer, std::filesystem::path const &path) {
        if (SDL_Texture *texture = IMG_LoadTexture(renderer.get(), path.string().c_str()); texture) {
            m_texture = {texture, SDL_DestroyTexture};
        } else {
            throw std::runtime_error(
                std::format("Could not load texture from path: {} ERROR: {}",
                            path.string(), SDL_GetError()));
        }
    }
} // game
