//
// Created by Riebers on 30.01.2025.
//

#pragma once
#include <filesystem>
#include <functional>
#include <memory>
#include <optional>

typedef struct _Mix_Music Mix_Music;

namespace game {
    class Music {
    private:
        using MusicOwner = std::unique_ptr<Mix_Music, std::function<void(Mix_Music *)> >;
        std::optional<MusicOwner> m_music;

    public:
        Music() = default;

        explicit Music(std::filesystem::path const &);

        void load(std::filesystem::path const &);

        [[nodiscard]] std::optional<Mix_Music *> get() const;

        [[nodiscard]] bool has_music() const;
    };
} // game
