//
// Created by HP on 25.12.2024.
//

#include "Text.hpp"

#include <utility>

#include "gamer/Renderer.hpp"

namespace game {
    Text::Text(Context const &context, const std::string &text, SDL_Rect const &rect, SDL_Color color,
               std::string const &id) : m_context(context), m_color(color), m_text(text), m_texture(nullptr),
                                        m_rect(rect),
                                        m_id(id) {
        set_text(m_text);
    }

    void Text::set_text(const std::string &text) {
        m_text = text;
        regenerateTexture();
    }

    void Text::render() const {
        if (m_texture) {
            m_context.renderer.render_whole_texture(m_texture.get(), m_rect);
            return;
        }
        throw std::runtime_error("Text: Invalid texture");
    }

    SDL_Rect Text::get_rect() const {
        return m_rect;
    }

    void Text::set_color(SDL_Color color) {
        m_color = color;
    }

    void Text::set_position(SDL_Point position) {
        m_rect.x = position.x;
        m_rect.y = position.y;
    }

    void Text::regenerateTexture() {
        if (auto const font = m_context.asset_store.get_font(m_id); font.has_font()) {
            if (std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface *s)> > surface{
                TTF_RenderText_Blended(font.get().value(), m_text.c_str(),
                                       m_color),
                [](SDL_Surface *s) { SDL_FreeSurface(s); }
            }; surface != nullptr) {
                if (std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)> > texture{
                    SDL_CreateTextureFromSurface(m_context.renderer.get(), surface.get()),
                    [](SDL_Texture *tex) { SDL_DestroyTexture(tex); }
                }; texture != nullptr) {
                    m_texture = std::move(texture);
                    m_rect.w = surface->w;
                    m_rect.h = surface->h;
                    return;
                }
            }
        }
        throw std::runtime_error("Text: Cannot create text texture");
    }
} // game
