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

    tl::expected<AssetContainer, std::string> AssetStore::load_fonts(AssetContainer const &container) {
        for (auto const &font: container.font_infos) {
            // m_fonts[font.id] = FontOwner{font.path, font.font_size};
            if (!m_assets.try_emplace(font.id, std::move(FontOwner{font.path, font.font_size})).second) {
                return tl::unexpected{std::format("ERROR: Font with id {} already loaded.", font.id)};
            }
        }
        return container;
    }

    // tl::expected<AssetContainer, std::string> AssetStore::load_sounds(AssetContainer const &container) {
    //     // for (auto const &sound: container.sound_infos) {
    //     //     if (!m_assets.try_emplace(sound.id, std::move(Sound{sound.path})).second) {
    //     //         return tl::unexpected{std::format("ERROR: Sound with id {} already loaded.", sound.id)};
    //     //     }
    //     // }
    //     return container;
    // }
    //
    tl::expected<AssetContainer, std::string> AssetStore::load_musics(AssetContainer const &container) {
        for (auto const &music: container.music_infos) {
            // m_assets[music.id] = MusicOwner{music.path};
            if (!m_assets.try_emplace(music.id, std::move(MusicOwner{music.path})).second) {
                return tl::unexpected{std::format("ERROR: Music  with id {} already loaded.", music.id)};
            }
        }
        return container;
    }

    void AssetStore::load_from_file(std::filesystem::path const &path,
                                    Renderer &renderer) {
        AssetStore store;
        AssetContainer::from_file(path)
                .and_then([&store](AssetContainer const &container) {
                    return store.load_fonts(container);
                })
                .and_then([&store](AssetContainer const &container) {
                    return store.load_musics(container);
                }).or_else([](std::string const &error_msg) {
                    throw std::runtime_error{error_msg};
                });
        // .and_then([&store](AssetContainer const &container) {
        //     return store.load_musics(container);
        // });
        // .and_then(
        //     [&store, &renderer](AssetContainer const &container) {
        //         return store.load_textures(container, renderer);
        //     })
        // .and_then([&store](AssetContainer const &container) { return store.load_fonts(container); })
        // .and_then(
        //     [&store](AssetContainer const &container) {
        //         return store.load_sounds(container);
        //     })
        // .and_then([&store](AssetContainer const &container) {
        //     return store.load_musics(container);
        // });
    }
} // game
