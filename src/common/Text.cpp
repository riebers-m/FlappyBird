//
// Created by HP on 25.12.2024.
//

#include "Text.hpp"

#include <utility>

namespace game {
    Text::Text(SDL_Renderer *renderer, std::shared_ptr<FontManager> font_manager, const std::string &text,
               SDL_Rect const &rect,
               SDL_Color color, asset_id id) : m_renderer(renderer), m_font_manager(std::move(font_manager)),
                                               m_color(color),
                                               m_text(text), m_texture(nullptr), m_rect(rect), m_id(id) {
        if (m_renderer == nullptr || m_font_manager == nullptr) {
            throw std::runtime_error("Cannot create text renderer");
        }
        set_text(m_text);
    }

    void Text::set_text(const std::string &text) {
        m_text = text;
        regenerateTexture();
    }

    void Text::render() const {
        if (m_texture) {
            SDL_RenderCopy(m_renderer, m_texture.get(), nullptr, &m_rect);
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
        if (std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface *s)> > surface{
            TTF_RenderText_Blended(m_font_manager->get_resource(m_id).get(), m_text.c_str(),
                                   m_color),
            [](SDL_Surface *s) { SDL_FreeSurface(s); }
        }; surface != nullptr) {
            if (std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)> > texture{
                SDL_CreateTextureFromSurface(m_renderer, surface.get()),
                [](SDL_Texture *tex) { SDL_DestroyTexture(tex); }
            }; texture != nullptr) {
                m_texture = std::move(texture);
                m_rect.w = surface->w;
                m_rect.h = surface->h;
                return;
            }
        }
        throw std::runtime_error("Text: Cannot create text texture");
    }
} // game
