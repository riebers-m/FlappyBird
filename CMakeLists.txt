cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MAJOR_VERSION 0)
set(CMAKE_MINOR_VERSION 1)

project(FlappyBird)

# Add Cmake Package Manager
include(cmake/CPM.cmake)

# Add SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

# Add GLM
CPMAddPackage(
        NAME glm
        GITHUB_REPOSITORY g-truc/glm
        GIT_TAG 1.0.1
        OPTIONS "GLM_BUILD_TESTS OFF" "BUILD_SHARED_LIBS OFF"
)
# Add spdlog
CPMAddPackage(
        NAME spdlog
        GITHUB_REPOSITORY gabime/spdlog
        VERSION 1.14.1
)

# Add cpptrace
CPMAddPackage(
        NAME cpptrace
        GITHUB_REPOSITORY jeremy-rifkin/cpptrace
        VERSION 0.7.3
)

# Add entt
CPMAddPackage(
        NAME entt
        GITHUB_REPOSITORY skypjack/entt
        VERSION 3.14.0
)


set(IMGUI_SRC
        $<$<CONFIG:Debug>:libs/imgui-1913/imconfig.h;
        libs/imgui-1913/imgui.cpp;
        libs/imgui-1913/imgui_demo.cpp;
        libs/imgui-1913/imgui_draw.cpp;
        libs/imgui-1913/imgui_internal.h;
        libs/imgui-1913/imgui_tables.cpp;
        libs/imgui-1913/imgui_widgets.cpp;
        libs/imgui-1913/imstb_rectpack.h;
        libs/imgui-1913/imstb_textedit.h;
        libs/imgui-1913/imstb_truetype.h;
        libs/imgui-1913/backends/imgui_impl_sdl2.h;
        libs/imgui-1913/backends/imgui_impl_sdl2.cpp;
        libs/imgui-1913/backends/imgui_impl_sdlrenderer2.h;
        libs/imgui-1913/backends/imgui_impl_sdlrenderer2.cpp;
        src/common/ImGuiLogDebugLog.cpp;
        src/common/ImGuiLogDebugLog.hpp;
        src/helpers/ImGuiRender.hpp>
)

add_executable(FlappyBird main.cpp ${IMGUI_SRC}
        src/gamer/Gamer.cpp
        src/gamer/Gamer.hpp
        src/gamer/Game.cpp
        src/gamer/Game.hpp
        src/gamer/Configuration.hpp
        src/gamer/Context.hpp
        src/common/Logger.hpp
        src/common/SpdLog.hpp
        src/common/Const.hpp
        src/state/BaseState.hpp
        src/state/States.hpp
        src/state/StateManager.cpp
        src/state/StateManager.hpp
        src/state/MenuState.hpp
        src/state/MenuState.cpp
        src/resource/ResourceManager.hpp
        src/resource/AssetIDs.hpp
        src/resource/TextureManager.hpp
        src/resource/TextureManager.cpp
        src/resource/FontManager.cpp
        src/resource/FontManager.hpp
        src/resource/AudioManager.cpp
        src/resource/AudioManager.hpp
        src/common/Button.cpp
        src/common/Button.hpp
        src/common/Text.cpp
        src/common/Text.hpp
        src/common/Drawer.cpp
        src/common/Drawer.hpp
        src/gamer/Registry.hpp
)

target_link_libraries(FlappyBird
        SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf SDL2_mixer::SDL2_mixer
        glm::glm
        spdlog::spdlog_header_only
        cpptrace::cpptrace
        EnTT::EnTT
)

target_include_directories(FlappyBird PRIVATE
        src
        $<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui-1913>
        $<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui-1913/backends>
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
            "${CMAKE_CURRENT_SOURCE_DIR}/assets" $<TARGET_FILE_DIR:FlappyBird>)
endif ()