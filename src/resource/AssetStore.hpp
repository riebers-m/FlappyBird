//
// Created by Riebers on 30.01.2025.
//

#pragma once
#include <variant>

#include "AssetContainer.hpp"
#include "gamer/Font.hpp"
#include "gamer/FontOwner.hpp"
#include "gamer/MusicOwner.hpp"
#include "gamer/SoundOwner.hpp"
#include "gamer/TextureOwner.hpp"
#include "json/Json.hpp"

namespace game {
    class AssetStore {
    private:
        using Asset = std::variant<std::monostate, FontOwner, MusicOwner, TextureOwner, SoundOwner>;
        std::unordered_map<std::string, Asset> m_assets;

        tl::expected<AssetContainer, std::string> load_textures(AssetContainer const &, Renderer &);

        tl::expected<AssetContainer, std::string> load_fonts(AssetContainer const &);

        tl::expected<AssetContainer, std::string> load_sounds(AssetContainer const &);

        tl::expected<AssetContainer, std::string> load_musics(AssetContainer const &);

    public:
        AssetStore() = default;

        void load_from_file(std::filesystem::path const &path, Renderer &);

        // Font font(std::string const &id) const {
        //     return Font{m_fonts.at(id).get().value_or(nullptr)};
        // }

        // template<typename T>
        // tl::expected<T &, errors> get_asset(std::string const &id);
    };
} // game
