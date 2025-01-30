//
// Created by Riebers on 30.01.2025.
//

#pragma once
#include <filesystem>
#include <functional>
#include <memory>

typedef struct _TTF_Font TTF_Font;

namespace game {
    class Font {
    private:
        using FontOwner = std::unique_ptr<TTF_Font, std::function<void(TTF_Font *)> >;
        std::optional<FontOwner> m_font;

    public:
        Font() = default;

        explicit Font(std::filesystem::path const &, size_t font_size);

        [[nodiscard]] std::optional<TTF_Font *> get() const;

        [[nodiscard]] bool has_font() const;

        void load(std::filesystem::path const &, size_t font_size);
    };
} // gamer
