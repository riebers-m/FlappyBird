//
// Created by Riebers on 30.01.2025.
//

#include "Font.hpp"
#include <SDL_ttf.h>

namespace game {
    Font::Font(std::filesystem::path const &path, size_t font_size) : m_font() {
        load(path, font_size);
    }

    void Font::load(std::filesystem::path const &path, size_t font_size) {
        if (TTF_Font *font = TTF_OpenFont(path.string().c_str(), font_size); font) {
            m_font = {font, TTF_CloseFont};
        } else {
            throw std::runtime_error(
                std::format("Could not load font from path: {} ERROR: {}",
                            path.string(), TTF_GetError()));
        }
    }

    std::optional<TTF_Font *> Font::get() const {
        if (has_font()) {
            return {m_font->get()};
        }
        return std::nullopt;
    }

    bool Font::has_font() const {
        return m_font.has_value();
    }
} // gamer
