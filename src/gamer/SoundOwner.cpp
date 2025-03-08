//
// Created by Riebers on 30.01.2025.
//

#include "SoundOwner.hpp"
#include <SDL_mixer.h>
#include <format>

namespace game {
    SoundOwner::SoundOwner(std::filesystem::path const &path) : m_sound() {
        load(path);
    }

    void SoundOwner::load(std::filesystem::path const &path) {
        if (Mix_Chunk *raw_chunk = Mix_LoadWAV(path.string().c_str());
            raw_chunk) {
            m_sound = {raw_chunk, Mix_FreeChunk};
        } else {
            throw std::runtime_error(
                    std::format("Could not load chunk from path: {} ERROR: {}",
                                path.string(), Mix_GetError()));
        }
    }

    std::optional<Mix_Chunk *> SoundOwner::get() const {
        if (has_sound()) {
            return {m_sound.value().get()};
        }
        return std::nullopt;
    }

    bool SoundOwner::has_sound() const { return m_sound.has_value(); }
} // namespace game
