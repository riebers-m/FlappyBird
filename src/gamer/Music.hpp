//
// Created by Riebers on 05.02.2025.
//

#pragma once
#include <optional>
#include <SDL_mixer.h>

namespace game {
    class Music {
    private:
        std::optional<Mix_Music *> m_music;

    public:
        explicit Music(Mix_Music *music) : m_music{} {
            if (music) {
                m_music = music;
            }
        }

        [[nodiscard]] std::optional<Mix_Music *> get() const {
            return m_music;
        }

        [[nodiscard]] bool has_music() const {
            return m_music.has_value();
        }
    };
}
