cmake_minimum_required(VERSION 3.19)
project(FlappyBird)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${PROJECT_SOURCE_DIR}/project_options.cmake)
include(${PROJECT_SOURCE_DIR}/dependencies.cmake)

flappy_bird_setup_dependencies()

set(CMAKE_MAJOR_VERSION 0)
set(CMAKE_MINOR_VERSION 1)

add_subdirectory(src)