//
// Created by Riebers on 03.01.2025.
//

#pragma once
#include <functional>
#include <memory>
#include <SDL_render.h>

struct SDL_Renderer;

namespace game {
    class Window;

    enum RendererFlags : std::uint32_t {
        Software = SDL_RENDERER_SOFTWARE,
        Accelerate = SDL_RENDERER_ACCELERATED,
        VSync = SDL_RENDERER_PRESENTVSYNC,
        TargetTexture = SDL_RENDERER_TARGETTEXTURE,
    };

    using RendererDeleter = std::function<void(SDL_Renderer *)>;

    class Renderer {
    private:
        std::unique_ptr<SDL_Renderer, RendererDeleter> m_renderer;

    public:
        explicit Renderer(Window const &, RendererFlags flags);

        [[nodiscard]] SDL_Renderer *get() const;

        void set_renderer_blend_mode() const;

        void clear() const;

        void set_draw_color(SDL_Color color) const;

        void render_texture(SDL_Texture *, SDL_Rect src, SDL_Rect dest) const;

        void render_whole_texture(SDL_Texture *, SDL_Rect dest) const;

        void draw_filled_circle(int centerX,
                                int centerY, int32_t radius, SDL_Color color = {0xFF, 0xFF, 0xFF, 0xFF}) const;
    };
} // game
