
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

add_executable(FlappyBird main.cpp ${IMGUI_SRC}
        gamer/Gamer.cpp
        gamer/Gamer.hpp
        gamer/Game.cpp
        gamer/Game.hpp
        gamer/Configuration.hpp
        gamer/Context.hpp
        common/Logger.hpp
        common/SpdLog.hpp
        common/Const.hpp
        state/BaseState.hpp
        state/States.hpp
        state/StateManager.cpp
        state/StateManager.hpp
        state/MenuState.hpp
        state/MenuState.cpp
        resource/ResourceManager.hpp
        resource/AssetIDs.hpp
        resource/TextureManager.hpp
        resource/TextureManager.cpp
        resource/FontManager.cpp
        resource/FontManager.hpp
        resource/AudioManager.cpp
        resource/AudioManager.hpp
        common/Button.cpp
        common/Button.hpp
        common/Text.cpp
        common/Text.hpp
        gamer/Registry.hpp
        gamer/Window.cpp
        gamer/Window.hpp
        gamer/Renderer.cpp
        gamer/Renderer.hpp
        gamer/Context.cpp
        components/Transform.hpp
)

target_link_libraries(FlappyBird
        SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf SDL2_mixer::SDL2_mixer
        glm::glm
        spdlog::spdlog_header_only
        cpptrace::cpptrace
        EnTT::EnTT
        JsonParser::JsonParser
        tl::expected
)

target_include_directories(FlappyBird PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/libs/imgui-1913>
        $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/libs/imgui-1913/backends>
)

set_target_properties(FlappyBird PROPERTIES
        CXX_STANDARD 20
        VERSION ${FlappyBird_VERSION}
        SOVERSION ${FlappyBird_VERSION_MAJOR}
)

if (WIN32)
    # Copy SDL2
    add_custom_command(TARGET FlappyBird POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_DIR}/../lib/x64/SDL2.dll" $<TARGET_FILE_DIR:FlappyBird>)
    # Copy SDL2_image
    add_custom_command(TARGET FlappyBird POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_IMAGE_DLL_DIR}/SDL2_image.dll" $<TARGET_FILE_DIR:FlappyBird>)
    # Copy SDL2_ttf
    add_custom_command(TARGET FlappyBird POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_TTF_DLL_DIR}/SDL2_ttf.dll" $<TARGET_FILE_DIR:FlappyBird>)
    # Copy SDL2_mixer
    add_custom_command(TARGET FlappyBird POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_MIXER_DLL_DIR}/SDL2_mixer.dll" $<TARGET_FILE_DIR:FlappyBird>)
    # Copy Fonts
    add_custom_command(TARGET FlappyBird POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/assets" $<TARGET_FILE_DIR:FlappyBird>)
endif ()