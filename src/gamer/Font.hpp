//
// Created by Riebers on 02.02.2025.
//

#pragma once
#include <optional>
#include <SDL_ttf.h>

namespace game {
    class Font {
    private:
        std::optional<TTF_Font *> m_font;

    public:
        explicit Font(TTF_Font *font) {
            if (font) {
                m_font = font;
            }
        }

        std::optional<TTF_Font *> get() const {
            return m_font;
        }

        [[nodiscard]] bool has_font() const {
            return m_font.has_value();
        }
    };
}
