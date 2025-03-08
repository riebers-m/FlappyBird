cmake_minimum_required(VERSION 3.19)
project(NanoEngine2D LANGUAGES CXX)

set(NanoEngine2D_VERSION_MAJOR 0)
set(NanoEngine2D_VERSION_MINOR 1)
set(NanoEngine2D_VERSION_PATCH 0)
set(NanoEngine2D_VERSION ${NanoEngine2D_VERSION_MAJOR}.${NanoEngine2D_VERSION_MINOR}.${NanoEngine2D_VERSION_PATCH})


include(${PROJECT_SOURCE_DIR}/project_options.cmake)
include(${PROJECT_SOURCE_DIR}/dependencies.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/version.cmake)

nanoengine_2d_setup_dependencies()

add_compile_definitions("$<$<CONFIG:DEBUG>:DEBUG>")

add_subdirectory(src)

if (${nanoengine_2d_build_tests})
    message(STATUS "Building engine tests")
    include(CTest)
    add_subdirectory(tests)
endif ()