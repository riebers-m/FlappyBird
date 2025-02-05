//
// Created by Riebers on 05.02.2025.
//

#pragma once
#include <optional>
#include <SDL_render.h>

namespace game {
    class Texture {
    private:
        std::optional<SDL_Texture *> m_texture;

    public:
        explicit Texture(SDL_Texture *texture) : m_texture() {
            if (texture) {
                m_texture = texture;
            }
        }

        [[nodiscard]] std::optional<SDL_Texture *> get() const {
            return m_texture;
        }

        [[nodiscard]] bool has_texture() const {
            return m_texture.has_value();
        }
    };
}
