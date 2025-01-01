//
// Created by Riebers on 31.12.2024.
//

#include "AudioManager.hpp"

namespace game {
    [[nodiscard]] std::shared_ptr<Mix_Chunk> AudioManager::get_chunk(asset_id id) const {
        return m_chunks.at(id);
    }

    [[nodiscard]] std::shared_ptr<Mix_Music> AudioManager::get_music(asset_id id) const {
        return m_music.at(id);
    }

    [[nodiscard]] bool AudioManager::has_chunk(asset_id id) const {
        return m_chunks.contains(id);
    }

    [[nodiscard]] bool AudioManager::has_music(asset_id id) const {
        return m_music.contains(id);
    }

    void AudioManager::clear() {
        m_chunks.clear();
        m_music.clear();
    }

    std::shared_ptr<Mix_Chunk> AudioManager::load_chunk(const std::filesystem::path &path) {
        Mix_Chunk *raw_chunk = Mix_LoadWAV(path.string().c_str());
        if (!raw_chunk) {
            throw std::runtime_error("Failed to load Mix_Chunk");
        }
        return {raw_chunk, Mix_FreeChunk};
    }

    std::shared_ptr<Mix_Music> AudioManager::load_music(const std::filesystem::path &path) {
        Mix_Music *raw_music = Mix_LoadMUS(path.string().c_str());
        if (!raw_music) {
            throw std::runtime_error("Failed to load Mix_Music");
        }
        return {raw_music, Mix_FreeMusic};
    }
} // game
