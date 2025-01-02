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
    )

    if (${flappy_bird_build_tests})
        CPMAddPackage(
                NAME GOOGLE_TEST
                GITHUB_REPOSITORY google/googletest
                VERSION 1.14.0
                OPTIONS
                "BUILD_GMOCK OFF"
                "INSTALL_GTEST OFF"
        )
    endif ()
endfunction()