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
    option(nanoengine_2d_warnings_as_errors "Treat warnings as errors" ON)
    option(nanoengine_2d_enable_undefined_behavior_sanitizer "Enable undefined behavior sanitizer" ${supports_ubsan})
    option(nanoengine_2d_enable_address_sanitizer "Enable address sanitizer" ${supports_asan})
    option(nanoengine_2d_enable_thread_sanitizer "Enable thread sanitizer" ${supports_thread_sanitizer})
    option(nanoengine_2d_build_examples "Build example server and client applications" OFF)
    option(nanoengine_2d_build_tests "Build tests using Catch2 Test" ON)
else ()
    option(nanoengine_2d_warnings_as_errors "Treat warnings as errors" OFF)
    option(nanoengine_2d_enable_undefined_behavior_sanitizer "Enable undefined behavior sanitizer" OFF)
    option(nanoengine_2d_enable_address_sanitizer "Enable address sanitizer" OFF)
    option(nanoengine_2d_enable_thread_sanitizer "Enable thread sanitizer" OFF)
    option(nanoengine_2d_build_examples "Build example server and client applications" OFF)
    option(nanoengine_2d_build_tests "Build tests using Catch2 Test" OFF)
endif ()

add_library(nanoengine_2d_warnings INTERFACE)
set_warnings(nanoengine_2d_warnings ${nanoengine_2d_warnings_as_errors})

add_library(nanoengine_2d_sanitizers INTERFACE)
enable_sanitizers(
        nanoengine_2d_sanitizers
        ${nanoengine_2d_enable_address_sanitizer}
        ${nanoengine_2d_enable_undefined_behavior_sanitizer}
        ${nanoengine_2d_enable_thread_sanitizer}
)

add_library(nanoengine_2d_options INTERFACE)
target_link_libraries(nanoengine_2d_options
        INTERFACE nanoengine_2d_warnings
        INTERFACE nanoengine_2d_sanitizers
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)