include("${PROJECT_SOURCE_DIR}/cmake/CPM.cmake")
include("${PROJECT_SOURCE_DIR}/cmake/system_link.cmake")

function(flappy_bird_setup_dependencies)
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

    # Add expected till we use c++23
    CPMAddPackage(
            NAME expected
            GITHUB_REPOSITORY TartanLlama/expected
            VERSION 1.1.0
            OPTIONS "EXPECTED_BUILD_TESTS OFF"
    )

    CPMAddPackage(
            NAME Json
            GITHUB_REPOSITORY riebers-m/Json
            VERSION 0.3.0
    )

    CPMAddPackage(
            NAME lua
            GITHUB_REPOSITORY walterschell/Lua
            VERSION 5.4.5
    )

    CPMAddPackage(
            NAME sol
            GITHUB_REPOSITORY ThePhD/sol2
            VERSION 3.3.0
    )

    if (${flappy_bird_build_tests})
        CPMAddPackage(
                NAME Catch2
                GITHUB_REPOSITORY catchorg/Catch2
                VERSION 3.7.1
                OPTIONS "CATCH_INSTALL_HELPERS OFF" "CATCH_BUILD_TESTING OFF" "CATCH_INSTALL_DOCS OFF"
        )
    endif ()
endfunction()