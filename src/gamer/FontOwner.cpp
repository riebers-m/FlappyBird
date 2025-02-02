//
// Created by Riebers on 30.01.2025.
//

#include "FontOwner.hpp"
#include <SDL_ttf.h>

namespace game {
    FontOwner &FontOwner::operator=(FontOwner &&other) noexcept {
        using std::swap;
        swap(m_font, other.m_font);
        return *this;
    }

    FontOwner::FontOwner(FontOwner &&other) noexcept {
        using std::swap;
        swap(m_font, other.m_font);
    }

    FontOwner::FontOwner(std::filesystem::path const &path, size_t font_size) : m_font() {
        load(path, font_size);
    }

    void FontOwner::load(std::filesystem::path const &path, size_t font_size) {
        if (TTF_Font *font = TTF_OpenFont(path.string().c_str(), font_size); font) {
            m_font = {font, TTF_CloseFont};
        } else {
            throw std::runtime_error(
                std::format("Could not load font from path: {} ERROR: {}",
                            path.string(), TTF_GetError()));
        }
    }

    std::optional<TTF_Font *> FontOwner::get() const {
        if (has_font()) {
            return {m_font->get()};
        }
        return std::nullopt;
    }

    bool FontOwner::has_font() const {
        return m_font.has_value();
    }
} // gamer
