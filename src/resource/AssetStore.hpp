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


namespace game {
    namespace detail {
        template<typename TAsset>
        struct AssetMapping;

        template<>
        struct AssetMapping<Font> {
            using Type = FontOwner;
        };

        template<>
        struct AssetMapping<Music> {
            using Type = MusicOwner;
        };

        template<>
        struct AssetMapping<Texture> {
            using Type = TextureOwner;
        };

        template<>
        struct AssetMapping<Sound> {
            using Type = SoundOwner;
        };
    }

    class AssetStore {
    private:
        using Asset = std::variant<std::monostate, FontOwner, MusicOwner, TextureOwner, SoundOwner,
            std::filesystem::path>;
        std::unordered_map<std::string, Asset> m_assets;

        tl::expected<AssetContainer, std::string> load_textures(AssetContainer const &, Renderer &);

        tl::expected<AssetContainer, std::string> load_fonts(AssetContainer const &);

        tl::expected<AssetContainer, std::string> load_sounds(AssetContainer const &);

        tl::expected<AssetContainer, std::string> load_musics(AssetContainer const &);

        tl::expected<AssetContainer, std::string> load_scripts(AssetContainer const &);

        template<typename TAsset>
        TAsset get_asset(std::string const &id) {
            using Owner = typename detail::AssetMapping<TAsset>::Type;
            if (m_assets.contains(id)) {
                if (std::holds_alternative<Owner>(m_assets.at(id))) {
                    return TAsset{std::get<Owner>(m_assets[id]).get().value()};
                }
            }
            return TAsset{nullptr};
        }

    public:
        AssetStore() = default;

        explicit AssetStore(std::filesystem::path const &path, Renderer &);

        void load_from_file(std::filesystem::path const &path, Renderer &);


        Font get_font(std::string const &id) {
            return get_asset<Font>(id);
        }

        Texture get_texture(std::string const &id) {
            return get_asset<Texture>(id);
        }

        Sound get_sound(std::string const &id) {
            return get_asset<Sound>(id);
        }

        Music get_music(std::string const &id) {
            return get_asset<Music>(id);
        }

        std::optional<std::filesystem::path> get_script_path(std::string const &id) {
            if (m_assets.contains(id)) {
                if (std::holds_alternative<std::filesystem::path>(m_assets.at(id))) {
                    return std::get<std::filesystem::path>(m_assets[id]);
                }
            }
            return std::nullopt;
        }
    };
} // game
