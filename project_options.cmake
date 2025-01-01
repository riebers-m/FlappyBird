include(${PROJECT_SOURCE_DIR}/cmake/warnings.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/sanitizers.cmake)

# the following function was taken from:
# https://github.com/cpp-best-practices/cmake_template/blob/main/ProjectOptions.cmake
macro(check_sanitizer_support)
    if ((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)
        set(supports_ubsan ON)
        set(supports_thread_sanitizer ON)
    else ()
        set(supports_ubsan OFF)
        set(supports_thread_sanitizer OFF)
    endif ()

    if ((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
        set(supports_asan OFF)
        set(supports_thread_sanitizer OFF)
    else ()
        set(supports_asan ON)
        set(supports_thread_sanitizer OFF)
    endif ()
endmacro()

check_sanitizer_support()

if (PROJECT_IS_TOP_LEVEL)
    option(flappy_bird_warnings_as_errors "Treat warnings as errors" ON)
    option(flappy_bird_enable_undefined_behavior_sanitizer "Enable undefined behavior sanitizer" ${supports_ubsan})
    option(flappy_bird_enable_address_sanitizer "Enable address sanitizer" ${supports_asan})
    option(flappy_bird_enable_thread_sanitizer "Enable thread sanitizer" ${supports_thread_sanitizer})
    option(flappy_bird_build_examples "Build example server and client applications" OFF)
    option(flappy_bird_build_tests "Build tests using Google Test" OFF)
else ()
    option(flappy_bird_warnings_as_errors "Treat warnings as errors" OFF)
    option(flappy_bird_enable_undefined_behavior_sanitizer "Enable undefined behavior sanitizer" OFF)
    option(flappy_bird_enable_address_sanitizer "Enable address sanitizer" OFF)
    option(flappy_bird_enable_thread_sanitizer "Enable thread sanitizer" OFF)
    option(flappy_bird_build_examples "Build example server and client applications" OFF)
    option(flappy_bird_build_tests "Build tests using Google Test" OFF)
endif ()

add_library(flappy_bird_warnings INTERFACE)
set_warnings(flappy_bird_warnings ${flappy_bird_warnings_as_errors})

add_library(flappy_bird_sanitizers INTERFACE)
enable_sanitizers(
        flappy_bird_sanitizers
        ${flappy_bird_enable_address_sanitizer}
        ${flappy_bird_enable_undefined_behavior_sanitizer}
        ${flappy_bird_enable_thread_sanitizer}
)

add_library(flappy_bird_options INTERFACE)
target_link_libraries(flappy_bird_options
        INTERFACE flappy_bird_warnings
        INTERFACE flappy_bird_sanitizers
)