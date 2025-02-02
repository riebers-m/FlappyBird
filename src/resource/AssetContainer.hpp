//
// Created by Riebers on 01.02.2025.
//

#pragma once
#include "json/Json.hpp"
#include <filesystem>
#include <fstream>
#include <format>

namespace game {
    struct TextureInfo {
        std::filesystem::path path;
        std::string id;
    };

    REGISTER_MEMBER(TextureInfo, path);
    REGISTER_MEMBER(TextureInfo, id);

    struct FontInfo {
        std::filesystem::path path;
        std::string id;
        std::size_t font_size;
    };

    REGISTER_MEMBER(FontInfo, path);
    REGISTER_MEMBER(FontInfo, id);
    REGISTER_MEMBER(FontInfo, font_size);

    struct SoundInfo {
        std::filesystem::path path;
        std::string id;
    };

    REGISTER_MEMBER(SoundInfo, path);
    REGISTER_MEMBER(SoundInfo, id);

    struct MusicInfo {
        std::filesystem::path path;
        std::string id;
    };

    REGISTER_MEMBER(MusicInfo, path);
    REGISTER_MEMBER(MusicInfo, id);

    struct AssetContainer {
        std::vector<TextureInfo> texture_infos;
        std::vector<FontInfo> font_infos;
        std::vector<SoundInfo> sound_infos;
        std::vector<MusicInfo> music_infos;

        static tl::expected<AssetContainer, std::string> from_file(std::filesystem::path const &path) {
            std::ifstream file{path};
            if (!file.is_open()) {
                return tl::unexpected{std::format("Could not read asset file for path: {}", path.string())};
            }
            std::string asset_file;
            file.seekg(0, std::ios::end);
            asset_file.reserve(file.tellg());
            file.seekg(0, std::ios::beg);

            // https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
            // istreambuf_iterator is a single-pass input iterator that reads successive characters from the
            // std::basic_streambuf object for which it was constructed.
            asset_file.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            AssetContainer container;
            if (auto const result = json::deserialize_type(asset_file, container); result.error != json::Error::ok) {
                return tl::unexpected
                        {"Could not deserialize asset file"};
            }
            return container;
        }
    };

    REGISTER_MEMBER(AssetContainer, texture_infos);
    REGISTER_MEMBER(AssetContainer, font_infos);
    REGISTER_MEMBER(AssetContainer, sound_infos);
    REGISTER_MEMBER(AssetContainer, music_infos);
}
