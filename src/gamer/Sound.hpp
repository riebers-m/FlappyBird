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
    class Sound {
    private:
        using SoundOwner = std::unique_ptr<Mix_Chunk, std::function<void(Mix_Chunk *)> >;
        std::optional<SoundOwner> m_sound;

    public:
        Sound() = default;

        Sound &operator=(Sound &&) noexcept;

        Sound(Sound &&) noexcept;

        explicit Sound(std::filesystem::path const &);

        void load(std::filesystem::path const &);

        [[nodiscard]] std::optional<Mix_Chunk *> get() const;

        [[nodiscard]] bool has_sound() const;
    };
} // game
