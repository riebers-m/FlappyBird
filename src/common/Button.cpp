//
// Created by riebers on 19.12.2024.
//

#include "Button.hpp"

#include <SDL_events.h>
#include <format>
#include <stdexcept>
#include <utility>

#include "Const.hpp"

namespace game {
    Button::Button(ContextPtr context, SDL_Rect const &bbox, const std::string &text,
                   std::function<void()> callback) : m_context(std::move(context)), m_bbox(bbox), m_text(text),
                                                     m_callback(std::move(callback)) {
        set_text(m_text, m_context->renderer, {});
    }


    void Button::set_bbox(SDL_Rect const &new_bbox) { m_bbox = new_bbox; }

    void Button::handle_events(SDL_Event const &event) {
        if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONUP ||
            event.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);

            m_inside = true;
            m_state = BUTTON_STATE::idle;

            if (x < m_bbox.x) {
                m_inside = false;
            } else if (x > m_bbox.x + m_bbox.w) {
                m_inside = false;
            } else if (y < m_bbox.y) {
                m_inside = false;
            } else if (y > m_bbox.y + m_bbox.h) {
                m_inside = false;
            }

            if (m_inside) {
                m_state = BUTTON_STATE::hover;
                if (event.type == SDL_MOUSEBUTTONUP) {
                    m_clicked = true;
                } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                    m_state = BUTTON_STATE::pressed;
                }
            }
        }
    }

    void Button::update() {
        if (m_clicked) {
            auto const sound = m_context->audio_manager->get_chunk(asset_id::click_sound);
            Mix_PlayChannel(-1, sound.get(), 0);
            m_clicked = false;
            if (m_callback) {
                m_callback();
            }
        }
    }

    void Button::render(SDL_Renderer *renderer) {
        if (m_state == BUTTON_STATE::idle) {
            set_text(m_text, renderer, PRIMARY_COLOR);
        } else if (m_state == BUTTON_STATE::hover) {
            set_text(m_text, renderer, ACCENT_COLOR);
        } else {
            set_text(m_text, renderer, SECONDARY_COLOR);
        }
        SDL_Rect label_rect = {m_bbox.x, m_bbox.y, m_bbox.w, m_bbox.h};
        SDL_RenderCopy(renderer, m_texture.get(), nullptr, &label_rect);
    }

    void Button::on_clicked(std::function<void()> callback) {
        m_callback = std::move(callback);
    }

    void Button::set_text(const std::string &text, SDL_Renderer *renderer, SDL_Color color) {
        if (std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface *s)> > surface{
            TTF_RenderText_Blended(m_context->font_manager->get_resource(asset_id::pico8_font_50).get(), m_text.c_str(),
                                   color),
            [](SDL_Surface *s) { SDL_FreeSurface(s); }
        }; surface != nullptr) {
            if (std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)> > texture{
                SDL_CreateTextureFromSurface(renderer, surface.get()), [](SDL_Texture *tex) { SDL_DestroyTexture(tex); }
            }; texture != nullptr) {
                m_texture = std::move(texture);
                int label_width, label_height;
                if (SDL_QueryTexture(m_texture.get(), nullptr, nullptr, &label_width, &label_height) != 0) {
                    throw std::runtime_error(std::format("Could not query texture: {}", SDL_GetError()));
                }
                m_bbox.w = label_width;
                m_bbox.h = label_height;
            }
        }
    }

    SDL_Rect Button::size() const {
        return m_bbox;
    }
} // namespace game
