//
// Created by Riebers on 30.01.2025.
//

#pragma once
#include <filesystem>
#include <functional>
#include <memory>
#include <optional>
// #include <SDL_mixer.h>
typedef struct _Mix_Music Mix_Music;

namespace game {
    class MusicOwner {
    private:
        using Owner = std::unique_ptr<Mix_Music, std::function<void(Mix_Music *)> >;
        std::optional<Owner> m_music;

    public:
        MusicOwner() = default;

        // MusicOwner(MusicOwner &&other) noexcept = default;
        //
        // MusicOwner &operator=(MusicOwner &&other) noexcept = default;
        //
        // MusicOwner &operator=(MusicOwner const &other) = delete;
        //
        // MusicOwner(MusicOwner const &other) = delete;

        //
        // MusicOwner &operator=(MusicOwner &&other) noexcept;
        //
        // MusicOwner(MusicOwner &&other) noexcept;

        explicit MusicOwner(std::filesystem::path const &);

        void load(std::filesystem::path const &);

        [[nodiscard]] std::optional<Mix_Music *> get() const;

        [[nodiscard]] bool has_music() const;
    };
} // game
