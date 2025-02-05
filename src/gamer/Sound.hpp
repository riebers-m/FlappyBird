//
// Created by Riebers on 05.02.2025.
//

#pragma once
#include <optional>
#include <SDL_mixer.h>

namespace game {
    class Sound {
    private:
        std::optional<Mix_Chunk *> m_sound;

    public:
        explicit Sound(Mix_Chunk *chunk) : m_sound() {
            if (chunk) {
                m_sound = chunk;
            }
        }

        [[nodiscard]] std::optional<Mix_Chunk *> get() const {
            return m_sound;
        }

        [[nodiscard]] bool has_sound() const {
            return m_sound.has_value();
        }
    };
}
