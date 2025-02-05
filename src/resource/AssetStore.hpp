//
// Created by Riebers on 30.01.2025.
//

#pragma once
#include <variant>

#include "AssetContainer.hpp"
#include "gamer/Font.hpp"
#include "gamer/FontOwner.hpp"
#include "gamer/Music.hpp"
#include "gamer/MusicOwner.hpp"
#include "gamer/Sound.hpp"
#include "gamer/SoundOwner.hpp"
#include "gamer/Texture.hpp"
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

        Font get_font(std::string const &id);

        Texture get_texture(std::string const &id) const;

        Sound get_sound(std::string const &id) const;

        Music get_music(std::string const &id) const;


        // template<typename T>
        // tl::expected<T &, errors> get_asset(std::string const &id);
    };
} // game
