//
// Created by Riebers on 30.01.2025.
//

#include "MusicOwner.hpp"
#include <SDL_mixer.h>

namespace game {
    // MusicOwner &MusicOwner::operator=(MusicOwner &&other) noexcept {
    //     using std::swap;
    //     swap(m_music, other.m_music);
    //
    //     return *this;
    // }
    //
    // MusicOwner::MusicOwner(MusicOwner &&other) noexcept {
    //     using std::swap;
    //     swap(m_music, other.m_music);
    // }

    MusicOwner::MusicOwner(std::filesystem::path const &path) : m_music() {
        load(path);
    }

    void MusicOwner::load(std::filesystem::path const &path) {
        if (Mix_Music *raw_music = Mix_LoadMUS(path.string().c_str()); raw_music) {
            m_music = {raw_music, Mix_FreeMusic};
        } else {
            throw std::runtime_error(
                std::format("Could not load music from path: {} ERROR: {}",
                            path.string(), Mix_GetError()));
        }
    }

    std::optional<Mix_Music *> MusicOwner::get() const {
        if (has_music()) {
            return {m_music.value().get()};
        }
        return std::nullopt;
    }

    bool MusicOwner::has_music() const {
        return m_music.has_value();
    }
} // game
