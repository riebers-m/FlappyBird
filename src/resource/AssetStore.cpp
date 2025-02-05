//
// Created by Riebers on 30.01.2025.
//

#include "AssetStore.hpp"
#include "AssetContainer.hpp"
#include "gamer/Renderer.hpp"

namespace game {
    // tl::expected<AssetContainer, std::string>
    // AssetStore::load_textures(AssetContainer const &container, Renderer &renderer) {
    //     // for (auto const &texture: container.texture_infos) {
    //     //     if (!m_assets.try_emplace(texture.id, std::move(Texture{renderer, texture.path})).second) {
    //     //         return tl::unexpected{std::format("ERROR: Texture with id {} already loaded.", texture.id)};
    //     //     }
    //     // }
    //     return container;
    // }

    tl::expected<AssetContainer, std::string> AssetStore::load_textures(AssetContainer const &container,
                                                                        Renderer &renderer) {
        for (auto const &texture: container.texture_infos) {
            if (!m_assets.try_emplace(texture.id, std::move(TextureOwner{renderer, texture.path})).second) {
                return tl::unexpected{std::format("ERROR: Texture with id {} already loaded.", texture.id)};
            }
        }
        return container;
    }

    tl::expected<AssetContainer, std::string> AssetStore::load_fonts(AssetContainer const &container) {
        for (auto const &font: container.font_infos) {
            if (!m_assets.try_emplace(font.id, std::move(FontOwner{font.path, font.font_size})).second) {
                return tl::unexpected{std::format("ERROR: Font with id {} already loaded.", font.id)};
            }
        }
        return container;
    }

    tl::expected<AssetContainer, std::string> AssetStore::load_sounds(AssetContainer const &container) {
        for (auto const &sound: container.sound_infos) {
            if (!m_assets.try_emplace(sound.id, std::move(SoundOwner{sound.path})).second) {
                return tl::unexpected{std::format("ERROR: Sound with id {} already loaded.", sound.id)};
            }
        }
        return container;
    }

    tl::expected<AssetContainer, std::string> AssetStore::load_musics(AssetContainer const &container) {
        for (auto const &music: container.music_infos) {
            if (!m_assets.try_emplace(music.id, std::move(MusicOwner{music.path})).second) {
                return tl::unexpected{std::format("ERROR: Music  with id {} already loaded.", music.id)};
            }
        }
        return container;
    }

    void AssetStore::load_from_file(std::filesystem::path const &path,
                                    Renderer &renderer) {
        AssetContainer::from_file(path).and_then([this](AssetContainer const &container) {
            return load_fonts(container);
        }).and_then([this](AssetContainer const &container) {
            return load_musics(container);
        }).and_then([this](AssetContainer const &container) {
            return load_sounds(container);
        }).and_then([this, &renderer](AssetContainer const &container) {
            return load_textures(container, renderer);
        }).or_else([](std::string const &error_msg) {
            throw std::runtime_error{error_msg};
        });
    }
} // game
