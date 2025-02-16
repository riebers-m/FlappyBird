//
// Created by riebers on 14.12.2024.
//

#pragma once
#include <filesystem>
#include <string>
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
} // namespace game

