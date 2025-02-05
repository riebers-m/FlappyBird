//
// Created by Riebers on 30.01.2025.
//

#pragma once
#include <filesystem>
#include <functional>
#include <memory>
#include <optional>
#include <SDL_mixer.h>
struct Mix_Chunk;

namespace game {
    class SoundOwner {
    private:
        using Owner = std::unique_ptr<Mix_Chunk, std::function<void(Mix_Chunk *)> >;
        std::optional<Owner> m_sound;

    public:
        SoundOwner() = default;

        SoundOwner &operator=(SoundOwner &&) noexcept = default;

        SoundOwner(SoundOwner &&) noexcept = default;

        SoundOwner(SoundOwner const &) noexcept = delete;

        SoundOwner &operator=(SoundOwner const &) noexcept = delete;

        explicit SoundOwner(std::filesystem::path const &);

        void load(std::filesystem::path const &);

        [[nodiscard]] std::optional<Mix_Chunk *> get() const;

        [[nodiscard]] bool has_sound() const;
    };
} // game
