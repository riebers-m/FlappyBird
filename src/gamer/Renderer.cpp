//
// Created by Riebers on 03.01.2025.
//

#include "Renderer.hpp"

#include <format>
#include <stdexcept>

#include "Window.hpp"

namespace game {
    Renderer::Renderer(Window const &window, RendererFlags flags) : m_renderer(
        std::unique_ptr<SDL_Renderer, RendererDeleter>(
            SDL_CreateRenderer(window.get(), -1, flags), [](SDL_Renderer *renderer) { SDL_DestroyRenderer(renderer); })
    ) {
        if (m_renderer == nullptr) {
            throw std::runtime_error(std::format("Failed to create SDL_Renderer: {}", SDL_GetError()));
        }
    }

    SDL_Renderer *Renderer::get() const {
        return m_renderer.get();
    }

    void Renderer::set_renderer_blend_mode() const {
        if (SDL_SetRenderDrawBlendMode(m_renderer.get(), SDL_BLENDMODE_BLEND) != 0) {
            throw std::runtime_error{std::format("could not set blend mode: {}", SDL_GetError())};
        }
    }

    void Renderer::clear() const {
        SDL_RenderClear(m_renderer.get());
    }

    void Renderer::set_draw_color(SDL_Color color) const {
        SDL_SetRenderDrawColor(m_renderer.get(), color.r, color.g, color.b, color.a);
    }

    void Renderer::render_texture(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest) const {
        SDL_RenderCopy(m_renderer.get(), texture, &src, &dest);
    }

    void Renderer::render_whole_texture(SDL_Texture *texture, SDL_Rect dest) const {
        SDL_RenderCopy(m_renderer.get(), texture, nullptr, &dest);
    }

    void Renderer::draw_filled_circle(int centerX, int centerY, int32_t radius,
                                      SDL_Color color) const {
        const auto squaredRadius = radius * radius;
        const int32_t minX = -radius;
        const int32_t minY = -radius;
        const auto maxX = radius;
        const auto maxY = radius;

        for (int y = minY; y <= maxY; ++y) {
            for (int x = minX; x <= maxX; ++x) {
                const auto distanceSquared = x * x + y * y;
                if (distanceSquared <= squaredRadius) {
                    SDL_RenderDrawPoint(m_renderer.get(), centerX + x, centerY + y);
                }
            }
        }
    }
} // game
