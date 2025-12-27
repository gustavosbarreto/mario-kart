cmake_minimum_required(VERSION 3.14)
project(common LANGUAGES C CXX)

# ------------------------------------------------------------------------------
# Global options
# ------------------------------------------------------------------------------
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

include(FetchContent)

# --- zlib ---
set(ZLIB_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(ZLIB_BUILD_STATIC ON CACHE BOOL "" FORCE)

FetchContent_Declare(
        zlib
        GIT_REPOSITORY https://github.com/madler/zlib.git
        GIT_TAG v1.3.1.2
)
FetchContent_MakeAvailable(zlib)

if(TARGET zlibstatic AND NOT TARGET ZLIB::ZLIB)
    add_library(ZLIB::ZLIB ALIAS zlibstatic)
endif()

# Ensure libpng sees the correct zlib include dirs
get_target_property(ZLIB_INCLUDE_DIRS zlibstatic INTERFACE_INCLUDE_DIRECTORIES)

# ------------------------------------------------------------------------------
# libpng (vendored)
# ------------------------------------------------------------------------------
set(PNG_SHARED OFF CACHE BOOL "" FORCE)
set(PNG_STATIC ON CACHE BOOL "" FORCE)
set(PNG_FRAMEWORK OFF CACHE BOOL "" FORCE)
set(PNG_TESTS OFF CACHE BOOL "" FORCE)
set(PNG_INSTALL OFF CACHE BOOL "" FORCE)
set(PNG_SKIP_INSTALL_ALL ON CACHE BOOL "" FORCE)
set(SKIP_INSTALL_ALL ON CACHE BOOL "" FORCE)
set(PNG_ZLIB_VERSION "external" CACHE STRING "" FORCE)
set(ZLIB_ROOT "${zlib_SOURCE_DIR}" CACHE PATH "" FORCE)
# Hint FindZLIB to use our built target
set(ZLIB_LIBRARY zlibstatic CACHE FILEPATH "" FORCE)
set(ZLIB_INCLUDE_DIR "${zlib_SOURCE_DIR}" CACHE PATH "" FORCE)
# Use prebuilt configuration header to avoid zlib version mismatches
set(PNG_LIBCONF_HEADER "${CMAKE_BINARY_DIR}/_deps/libpng-src/scripts/pnglibconf.h.prebuilt" CACHE FILEPATH "" FORCE)
set(ZLIB_BUILD_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    libpng
    GIT_REPOSITORY https://github.com/glennrp/libpng.git
    GIT_TAG        v1.6.53
)
FetchContent_MakeAvailable(libpng)

# ------------------------------------------------------------------------------
# SDL2_image options
# ------------------------------------------------------------------------------
set(SDL2IMAGE_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL2IMAGE_DEPS_SHARED OFF CACHE BOOL "" FORCE)
set(SDL2IMAGE_VENDORED ON CACHE BOOL "" FORCE)

# Disable AVIF / dav1d (avoids NASM dependency)
set(SDL2IMAGE_AVIF OFF CACHE BOOL "" FORCE)
set(SDL2IMAGE_VENDORED_DAV1D OFF CACHE BOOL "" FORCE)

# Disable TIFF (avoids libtiff dependency)
set(SDL2IMAGE_TIF OFF CACHE BOOL "" FORCE)
set(SDL2IMAGE_TIFF OFF CACHE BOOL "" FORCE)

# ------------------------------------------------------------------------------
# SDL2_ttf options
# ------------------------------------------------------------------------------
set(SDL2TTF_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL2TTF_VENDORED ON CACHE BOOL "" FORCE)

# ------------------------------------------------------------------------------
# SDL audio/video backends (Linux only)
# ------------------------------------------------------------------------------
if(UNIX AND NOT APPLE)
    set(SDL_AUDIO_DRIVER_ALSA       ON CACHE BOOL "" FORCE)
    set(SDL_AUDIO_DRIVER_PULSEAUDIO ON CACHE BOOL "" FORCE)
    set(SDL_AUDIO_DRIVER_PIPEWIRE   ON CACHE BOOL "" FORCE)

    set(SDL_VIDEO_X11     ON CACHE BOOL "" FORCE)
    set(SDL_VIDEO_WAYLAND ON CACHE BOOL "" FORCE)
endif()

# ------------------------------------------------------------------------------
# SDL dependencies
# ------------------------------------------------------------------------------
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-2.32.10
    GIT_SHALLOW    TRUE
)

FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG        release-2.8.8
    GIT_SHALLOW    TRUE
)

FetchContent_Declare(
    SDL2_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG        release-2.24.0
    GIT_SHALLOW    TRUE
)

FetchContent_MakeAvailable(SDL2 SDL2_image SDL2_ttf)

# ------------------------------------------------------------------------------
# Include paths (from FetchContent build tree)
# ------------------------------------------------------------------------------
set(SDL2_INCLUDE_DIRS        "${CMAKE_BINARY_DIR}/_deps/sdl2-src/include")
set(SDL2_IMAGE_INCLUDE_DIRS  "${CMAKE_BINARY_DIR}/_deps/sdl2_image-src/include")
set(SDL2_TTF_INCLUDE_DIRS    "${CMAKE_BINARY_DIR}/_deps/sdl2_ttf-src")

# ------------------------------------------------------------------------------
# Common static library
# ------------------------------------------------------------------------------
add_library(common STATIC
    allegro.cpp
    AllegroSystem.cpp
    AllegroScreen.cpp
    AllegroKeyboard.cpp
    SuperMode7.cpp
    ObjectSize.cpp
    Vector.cpp
    Track.cpp
)

target_include_directories(common
    PUBLIC
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# On Windows with static SDL2, we need to handle SDL_main manually
if(WIN32)
    target_compile_definitions(common PUBLIC SDL_MAIN_HANDLED)
endif()

target_link_libraries(common
    PUBLIC
        SDL2::SDL2-static
        SDL2_image::SDL2_image-static
        SDL2_ttf::SDL2_ttf-static
        png_static
        zlibstatic
)
