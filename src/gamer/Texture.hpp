//
// Created by Riebers on 26.01.2025.
//

#pragma once
#include <filesystem>
#include <functional>
#include <memory>

#include "resource/TextureManager.hpp"

struct SDL_Texture;

namespace game {
    class Renderer;

    class Texture {
    private:
        using TextureHandle = std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)> >;
        std::optional<TextureHandle> m_texture;

    public:
        Texture() = default;

        explicit Texture(Renderer &renderer, std::filesystem::path const &);

        [[nodiscard]] std::optional<SDL_Texture *> get() const;

        [[nodiscard]] bool has_texture() const;

        void load(const Renderer &renderer, std::filesystem::path const &);
    };
} // game
