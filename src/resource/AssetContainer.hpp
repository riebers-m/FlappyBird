//
// Created by Riebers on 01.02.2025.
//

#pragma once
#include "json/Json.hpp"
#include <filesystem>
#include <fstream>
#include <format>

#include "helpers/FileReader.hpp"

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

    struct ScriptInfo {
        std::filesystem::path path;
        std::string id;
    };

    struct AssetContainer {
        std::vector<TextureInfo> texture_infos;
        std::vector<FontInfo> font_infos;
        std::vector<SoundInfo> sound_infos;
        std::vector<MusicInfo> music_infos;
        std::vector<ScriptInfo> script_infos;

        static tl::expected<AssetContainer, std::string> from_file(std::filesystem::path const &path) {
            return FileReader::read_file(path)
                    .and_then([](std::string const &file) -> tl::expected<AssetContainer, std::string> {
                        AssetContainer container;
                        if (auto const result = json::deserialize_type(file, container);
                            result.error != json::Error::ok) {
                            return tl::unexpected
                                    {"Could not deserialize asset file"};
                        }
                        return container;
                    });
        }
    };

    REGISTER_MEMBER(AssetContainer, texture_infos);
    REGISTER_MEMBER(AssetContainer, font_infos);
    REGISTER_MEMBER(AssetContainer, sound_infos);
    REGISTER_MEMBER(AssetContainer, music_infos);
    REGISTER_MEMBER(AssetContainer, script_infos);
}
