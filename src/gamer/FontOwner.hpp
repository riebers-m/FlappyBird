//
// Created by Riebers on 30.01.2025.
//

#pragma once
#include <filesystem>
#include <functional>
#include <memory>

typedef struct _TTF_Font TTF_Font;

namespace game {
    class FontOwner {
    private:
        using Owner = std::unique_ptr<TTF_Font, std::function<void(TTF_Font *)> >;
        std::optional<Owner> m_font;

    public:
        FontOwner() = default;

        FontOwner(FontOwner &&other) noexcept = default;

        FontOwner &operator=(FontOwner &&other) noexcept = default;

        FontOwner(FontOwner const &) = delete;

        FontOwner &operator=(FontOwner const &) = delete;

        explicit FontOwner(std::filesystem::path const &, size_t font_size);

        [[nodiscard]] std::optional<TTF_Font *> get() const;

        [[nodiscard]] bool has_font() const;

        void load(std::filesystem::path const &, size_t font_size);
    };
} // gamer
