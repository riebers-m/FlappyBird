//
// Created by Riebers on 01.02.2025.
//

#include <catch2/catch_all.hpp>
#include "resource/AssetContainer.hpp"

TEST_CASE("Load asset container") {
    game::AssetContainer container;
    SECTION("empty object", "[json]") {
        auto const result = json::deserialize_type(R"()", container);
        REQUIRE(result.error == json::Error::ok);
    }
    SECTION("simple lists", "[json]") {
        auto const result = json::deserialize_type(
            R"({"texture_infos":[{"path":"/assets/textures/test1", "id":"texture-1"}],"font_infos":[{"path":"/assets/fonts/test1", "id":"font-1", "font_size":15}],
                        "music_infos":[{"path":"/assets/music/test1", "id":"music-1"}],"sound_infos":[{"path":"/assets/sounds/test1", "id":"sound-1"}]})",
            container);
        REQUIRE(result.error == json::Error::ok);
        REQUIRE(container.font_infos.back().font_size == 15);
        REQUIRE(container.font_infos.back().id == "font-1");
        REQUIRE(container.font_infos.back().path == std::filesystem::path{"/assets/fonts/test1"});
        REQUIRE(container.sound_infos.back().id == "sound-1");
        REQUIRE(container.sound_infos.back().path == "/assets/sounds/test1");
        REQUIRE(container.music_infos.back().id == "music-1");
        REQUIRE(container.music_infos.back().path == "/assets/music/test1");
        REQUIRE(container.texture_infos.back().id == "texture-1");
        REQUIRE(container.texture_infos.back().path == "/assets/textures/test1");
    }
    SECTION("missing fields", "[json]") {
        auto const result = json::deserialize_type(R"({"texture_infos":[{"id":"texture-1"}]})", container);
        REQUIRE(result.error == json::Error::ok);
        REQUIRE(container.texture_infos.back().id == "texture-1");
        REQUIRE(container.texture_infos.back().path.empty());
    }
    SECTION("invalid types", "[json]") {
        auto const result = json::deserialize_type(
            R"({"font_infos":[{"path":"/assets/fonts/test1", "id":"font-1", "font_size":"fifteen"}]})", container);
        REQUIRE(result.error != json::Error::ok);
    }
    SECTION("multiple entries", "[json]") {
        auto const result = json::deserialize_type(R"({"font_infos":[{"path":"/assets/fonts/test1",
        "id":"font-1", "font_size":15}, {"path":"/assets/fonts/test2", "id":"font-2", "font_size":20}]})", container);
        REQUIRE(result.error == json::Error::ok);
        REQUIRE(container.font_infos.size() == 2);
        REQUIRE(container.font_infos[0].font_size == 15);
        REQUIRE(container.font_infos[0].id == "font-1");
        REQUIRE(container.font_infos[0].path == "/assets/fonts/test1");
        REQUIRE(container.font_infos[1].font_size == 20);
        REQUIRE(container.font_infos[1].id == "font-2");
        REQUIRE(container.font_infos[1].path == "/assets/fonts/test2");
    }
    SECTION("special path characters", "[json]") {
        auto const result = json::deserialize_type(
            R"({"sound_infos":[{"path":"C:\\Users\\Test\\sound.wav", "id":"sound-1"}]})", container);
        REQUIRE(result.error == json::Error::ok);
        REQUIRE(container.sound_infos.size() == 1);
        REQUIRE(container.sound_infos[0].id == "sound-1");
        REQUIRE(container.sound_infos[0].path == "C:\\Users\\Test\\sound.wav");
    }
}
