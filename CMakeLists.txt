cmake_minimum_required(VERSION 3.16)

project(mario_kart LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Dependencies via pkg-config
find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)

# Common library in subdirectory
add_subdirectory(Common)

# Subdirectories for executables
add_subdirectory(Game)
add_subdirectory(TrackEditor)

# Convenience targets
add_custom_target(run-game
    COMMAND $<TARGET_FILE:game>
    DEPENDS game
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(run-editor
    COMMAND $<TARGET_FILE:editor>
    DEPENDS editor
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# Print summary
message(STATUS "SDL2 include: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2_ttf include: ${SDL2_TTF_INCLUDE_DIRS}")
message(STATUS "SDL2_image include: ${SDL2_IMAGE_INCLUDE_DIRS}")
