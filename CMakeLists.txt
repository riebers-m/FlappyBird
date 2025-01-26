cmake_minimum_required(VERSION 3.19)
project(FlappyBird LANGUAGES CXX)

set(FlappyBird_VERSION_MAJOR 0)
set(FlappyBird_VERSION_MINOR 1)
set(FlappyBird_VERSION_PATCH 0)
set(FlappyBird_VERSION ${FlappyBird_VERSION_MAJOR}.${FlappyBird_VERSION_MINOR}.${FlappyBird_VERSION_PATCH})


include(${PROJECT_SOURCE_DIR}/project_options.cmake)
include(${PROJECT_SOURCE_DIR}/dependencies.cmake)

flappy_bird_setup_dependencies()

add_subdirectory(src)

if (${flappy_bird_build_tests})
    message(STATUS "Building engine tests")
    include(CTest)
    add_subdirectory(tests)
endif ()