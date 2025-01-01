//
// Created by riebers on 20.12.2024.
//

#pragma once
#include <SDL_ttf.h>


#include "ResourceManager.hpp"
#include "common/Logger.hpp"

namespace game {
    class FontManager : public ResourceManager<FontManager, TTF_Font> {
    private:
        LoggerPtr m_logger;

    public:
        explicit FontManager(LoggerPtr);

        [[nodiscard]] std::shared_ptr<TTF_Font>
        load(std::filesystem::path const &, std::uint16_t font_size) const;
    };
} // namespace game
