//
// Created by riebers on 20.12.2024.
//

#include "FontManager.hpp"

namespace game {
    FontManager::FontManager(LoggerPtr logger) : m_logger(std::move(logger)) {
    }

    std::shared_ptr<TTF_Font>
    FontManager::load(std::filesystem::path const &path, std::uint16_t font_size) const {
        if (TTF_Font *font = TTF_OpenFont(path.string().c_str(), font_size); font) {
            return {font, [](TTF_Font *f) { TTF_CloseFont(f); }};
        }
        throw std::runtime_error(
            std::format("Could not load font from path: {} ERROR: {}",
                        path.string(), TTF_GetError()));
    }
} // namespace game
