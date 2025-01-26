add_executable(ecs_tests ecs_tests.cpp)
target_link_libraries(ecs_tests PRIVATE Catch2::Catch2WithMain ecslib::ecslib)
set_target_properties(ecs_tests PROPERTIES CXX_STANDARD 20)
add_test(ecs_tests COMMAND ecs_tests)


add_executable(asset_tests asset_tests.cpp
        ${CMAKE_SOURCE_DIR}/src/gamer/Texture.cpp
        ${CMAKE_SOURCE_DIR}/src/gamer/Renderer.cpp
        ${CMAKE_SOURCE_DIR}/src/gamer/Window.cpp
)
target_include_directories(asset_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(asset_tests PRIVATE Catch2::Catch2WithMain SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf SDL2_mixer::SDL2_mixer)
set_target_properties(asset_tests PROPERTIES CXX_STANDARD 20)
add_test(assets_tests COMMAND assets_tests)

# copy assets
add_custom_command(TARGET asset_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets" $<TARGET_FILE_DIR:asset_tests>)

if (WIN32)
    # Copy SDL2
    add_custom_command(TARGET asset_tests POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_DIR}/../lib/x64/SDL2.dll" $<TARGET_FILE_DIR:asset_tests>)
    # Copy SDL2_image
    add_custom_command(TARGET asset_tests POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_IMAGE_DLL_DIR}/SDL2_image.dll" $<TARGET_FILE_DIR:asset_tests>)
    # Copy SDL2_ttf
    add_custom_command(TARGET asset_tests POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_TTF_DLL_DIR}/SDL2_ttf.dll" $<TARGET_FILE_DIR:asset_tests>)
    # Copy SDL2_mixer
    add_custom_command(TARGET asset_tests POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_MIXER_DLL_DIR}/SDL2_mixer.dll" $<TARGET_FILE_DIR:asset_tests>)
endif ()