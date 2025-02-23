//
// Created by riebers on 14.12.2024.
//

#pragma once
#include <filesystem>
#include <string>

#include "helpers/FileReader.hpp"
#include "json/Json.hpp"

namespace game {
    struct EngineConfiguration {
        std::filesystem::path assetDirectory{"assets"};
        std::uint32_t gameResolutionWidth{1080};
        std::uint32_t gameResolutionHeight{720};
        bool displayMode{false};
        float aspectRationWidth{1.0};
        float aspectRationHeight{1.0};
        bool gameFullscreen{false};
        std::string title{"NanoEngine"};
    };

    REGISTER_MEMBER(EngineConfiguration, assetDirectory);
    REGISTER_MEMBER(EngineConfiguration, gameResolutionWidth);
    REGISTER_MEMBER(EngineConfiguration, gameResolutionHeight);
    REGISTER_MEMBER(EngineConfiguration, displayMode);
    REGISTER_MEMBER(EngineConfiguration, aspectRationWidth);
    REGISTER_MEMBER(EngineConfiguration, aspectRationHeight);
    REGISTER_MEMBER(EngineConfiguration, gameFullscreen);
    REGISTER_MEMBER(EngineConfiguration, title);

    inline EngineConfiguration load_config() {
        EngineConfiguration config;
        FileReader::read_file("nanoengine.config.json")
                .map([&config](std::string const &content) -> EngineConfiguration {
                    if (auto const result = json::deserialize_type(content, config);
                        result.error != json::Error::ok) {
                        throw std::runtime_error{"Could not deserialize nanoengine.config.json"};
                    }
                    return config;
                }).or_else([](std::string const &err) {
                    throw std::runtime_error(err);
                });;
        return config;
    }
} // namespace game

