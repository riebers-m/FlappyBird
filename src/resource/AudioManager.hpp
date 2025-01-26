//
// Created by Riebers on 31.12.2024.
//

#pragma once
#include <SDL_mixer.h>
#include <variant>

#include "ResourceManager.hpp"

namespace game {
    enum class AudioType {
        chunk,
        music
    };

    using Audio = std::variant<Mix_Chunk, Mix_Music>;

    class AudioManager : public ResourceManager<AudioManager, void> {
    private:
        // std::unordered_map<asset_id, std::shared_ptr<Mix_Chunk> > m_chunks;
        // std::unordered_map<asset_id, std::shared_ptr<Mix_Music> > m_music;

    public:
        template<typename... Args>
        std::shared_ptr<Audio> load(AudioType type, const asset_id &id, Args &&... args) {
            if (type == AudioType::chunk) {
                // auto chunk = load_chunk(std::forward<Args>(args)...);
                // m_chunks.emplace(id, chunk);
                // return chunk;
                return load_chunk(std::forward<Args>(args)...);
            }
            if (type == AudioType::music) {
                // auto music = load_music(std::forward<Args>(args)...);
                // m_music.emplace(id, music);
                // return music;
                return load_music(std::forward<Args>(args)...);
            }
            throw std::invalid_argument("Unknown AudioType");
        }

        // [[nodiscard]] std::shared_ptr<Mix_Chunk> get_chunk(asset_id id) const;
        //
        // [[nodiscard]] std::shared_ptr<Mix_Music> get_music(asset_id id) const;
        //
        // [[nodiscard]] bool has_chunk(asset_id id) const;
        //
        // [[nodiscard]] bool has_music(asset_id id) const;
        //
        // void clear();

    private:
        std::shared_ptr<Mix_Chunk> load_chunk(const std::filesystem::path &path);

        std::shared_ptr<Mix_Music> load_music(const std::filesystem::path &path);
    };
} // game
