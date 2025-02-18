
set(IMGUI_SRC
        $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/libs/imgui-1913/imconfig.h;
        ${CMAKE_SOURCE_DIR}/libs/imgui-1913/imgui.cpp;
        ${CMAKE_SOURCE_DIR}/libs/imgui-1913/imgui_demo.cpp;
        ${CMAKE_SOURCE_DIR}/libs/imgui-1913/imgui_draw.cpp;
        ${CMAKE_SOURCE_DIR}/libs/imgui-1913/imgui_internal.h;
        ${CMAKE_SOURCE_DIR}/libs/imgui-1913/imgui_tables.cpp;
        ${CMAKE_SOURCE_DIR}/libs/imgui-1913/imgui_widgets.cpp;
        ${CMAKE_SOURCE_DIR}/libs/imgui-1913/imstb_rectpack.h;
        ${CMAKE_SOURCE_DIR}/libs/imgui-1913/imstb_textedit.h;
        ${CMAKE_SOURCE_DIR}/libs/imgui-1913/imstb_truetype.h;
        ${CMAKE_SOURCE_DIR}/libs/imgui-1913/backends/imgui_impl_sdl2.h;
        ${CMAKE_SOURCE_DIR}/libs/imgui-1913/backends/imgui_impl_sdl2.cpp;
        ${CMAKE_SOURCE_DIR}/libs/imgui-1913/backends/imgui_impl_sdlrenderer2.h;
        ${CMAKE_SOURCE_DIR}/libs/imgui-1913/backends/imgui_impl_sdlrenderer2.cpp;
        common/ImGuiLogDebugLog.cpp;
        common/ImGuiLogDebugLog.hpp;
        helpers/ImGuiRender.hpp>
)

add_library(ecslib STATIC
        ecs/Entity.cpp
        ecs/Entity.hpp
        ecs/components/Transform.hpp
        ecs/components/RigidBody.hpp
        ecs/systems/ScriptHelpers.cpp
        ecs/systems/ScriptHelpers.hpp
        ecs/systems/Script.cpp
        ecs/systems/Script.hpp
)
target_link_libraries(ecslib PUBLIC EnTT::EnTT lua_static sol2::sol2 glm::glm)
target_include_directories(ecslib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(ecslib PROPERTIES
        CXX_STANDARD 20
)
add_library(ecslib::ecslib ALIAS ecslib)

add_executable(nanoengine2d main.cpp
        ${IMGUI_SRC}
        gamer/Gamer.cpp
        gamer/Gamer.hpp
        gamer/Game.cpp
        gamer/Game.hpp
        gamer/Context.hpp
        state/BaseState.hpp
        state/States.hpp
        state/StateManager.cpp
        state/StateManager.hpp
        state/MenuState.hpp
        state/MenuState.cpp
        common/Button.cpp
        common/Button.hpp
        common/Text.cpp
        common/Text.hpp
        gamer/Window.cpp
        gamer/Window.hpp
        gamer/Renderer.cpp
        gamer/Renderer.hpp
        gamer/Context.cpp
        gamer/Game.cpp
        gamer/Game.hpp
        gamer/TextureOwner.cpp
        gamer/TextureOwner.hpp
        gamer/FontOwner.cpp
        gamer/FontOwner.hpp
        gamer/SoundOwner.cpp
        gamer/SoundOwner.hpp
        gamer/MusicOwner.cpp
        gamer/MusicOwner.hpp
        resource/AssetStore.cpp
        resource/AssetStore.hpp
        common/Logger.hpp
        common/SpdLog.hpp
        gamer/EngineConfiguration.hpp
        common/Const.hpp
        gamer/Errors.hpp
        resource/AssetContainer.hpp
        gamer/Font.hpp
        gamer/Music.hpp
        gamer/Texture.hpp
        gamer/Sound.hpp
        helpers/FileReader.cpp
        helpers/FileReader.hpp
        sprite/SpriteSheet.cpp
        sprite/SpriteSheet.hpp
        version.hpp.in
        common/Delegate.hpp
        common/Input.cpp
        common/Input.hpp
        ecs/systems/RenderSystem.cpp
        ecs/systems/RenderSystem.hpp
        ecs/systems/SystemsManager.hpp
        ecs/components/Sprite.hpp
        ecs/systems/BaseSystem.hpp
        ecs/systems/MovementSystem.cpp
        ecs/systems/MovementSystem.hpp
)
target_link_libraries(nanoengine2d
        spdlog::spdlog_header_only
        JsonParser::JsonParser
        tl::expected
        glm::glm
        ecslib::ecslib
        SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf SDL2_mixer::SDL2_mixer
        cpptrace::cpptrace
)

target_include_directories(nanoengine2d PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/libs/imgui-1913>
        $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/libs/imgui-1913/backends>
)

set_target_properties(nanoengine2d PROPERTIES
        CXX_STANDARD 20
        VERSION ${FlappyBird_VERSION}
        SOVERSION ${FlappyBird_VERSION_MAJOR}
)

# copy nanoeengine.config.json
add_custom_command(TARGET nanoengine2d POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/nanoengine.config.json" $<TARGET_FILE_DIR:nanoengine2d>)

if (WIN32)
    # Copy SDL2
    add_custom_command(TARGET nanoengine2d POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_DIR}/../lib/x64/SDL2.dll" $<TARGET_FILE_DIR:nanoengine2d>)
    # Copy SDL2_image
    add_custom_command(TARGET nanoengine2d POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_IMAGE_DLL_DIR}/SDL2_image.dll" $<TARGET_FILE_DIR:nanoengine2d>)
    # Copy SDL2_ttf
    add_custom_command(TARGET nanoengine2d POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_TTF_DLL_DIR}/SDL2_ttf.dll" $<TARGET_FILE_DIR:nanoengine2d>)
    # Copy SDL2_mixer
    add_custom_command(TARGET nanoengine2d POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_MIXER_DLL_DIR}/SDL2_mixer.dll" $<TARGET_FILE_DIR:nanoengine2d>)
endif ()