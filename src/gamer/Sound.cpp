//
// Created by Riebers on 30.01.2025.
//

#include "Sound.hpp"
#include <SDL_mixer.h>

namespace game {
    Sound &Sound::operator=(Sound &&other) noexcept {
        using std::swap;
        swap(m_sound, other.m_sound);
        return *this;
    }

    Sound::Sound(Sound &&other) noexcept {
        using std::swap;
        swap(m_sound, other.m_sound);
    }

    Sound::Sound(std::filesystem::path const &path) : m_sound() {
        load(path);
    }

    void Sound::load(std::filesystem::path const &path) {
        if (Mix_Chunk *raw_chunk = Mix_LoadWAV(path.string().c_str()); raw_chunk) {
            m_sound = {raw_chunk, Mix_FreeChunk};
        } else {
            throw std::runtime_error(
                std::format("Could not load chunk from path: {} ERROR: {}",
                            path.string(), Mix_GetError()));
        }
    }

    std::optional<Mix_Chunk *> Sound::get() const {
        if (has_sound()) {
            return {m_sound.value().get()};
        }
        return std::nullopt;
    }

    bool Sound::has_sound() const {
        return m_sound.has_value();
    }
} // game
