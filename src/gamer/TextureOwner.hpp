//
// Created by Riebers on 26.01.2025.
//

#pragma once
#include <filesystem>
#include <functional>
#include <memory>
#include <optional>

struct SDL_Texture;

namespace game {
    class Renderer;

    class TextureOwner {
    private:
        using Owner = std::unique_ptr<SDL_Texture,
                                      std::function<void(SDL_Texture *)>>;
        std::optional<Owner> m_texture;

    public:
        TextureOwner() = default;

        TextureOwner &operator=(TextureOwner &&) noexcept = default;

        TextureOwner(TextureOwner &&) noexcept = default;

        TextureOwner &operator=(TextureOwner const &) = delete;

        TextureOwner(TextureOwner const &) = delete;

        explicit TextureOwner(Renderer &renderer,
                              std::filesystem::path const &);

        [[nodiscard]] std::optional<SDL_Texture *> get() const;

        [[nodiscard]] bool has_texture() const;

        void load(const Renderer &renderer, std::filesystem::path const &);
    };
} // namespace game
