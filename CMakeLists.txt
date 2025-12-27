cmake_minimum_required(VERSION 3.16)

project(mario_kart LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Dependencies via pkg-config (Linux/macOS) or find_package (Windows/vcpkg)
find_package(PkgConfig QUIET)

if(PkgConfig_FOUND)
  # Linux/macOS: use pkg-config
  pkg_check_modules(SDL2 REQUIRED sdl2)
  pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
  pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
else()
  # Windows: use find_package with vcpkg
  find_package(SDL2 REQUIRED CONFIG)
  find_package(SDL2_ttf REQUIRED CONFIG)
  find_package(SDL2_image REQUIRED CONFIG)
endif()

# Common library in subdirectory
add_subdirectory(src/common)

# Subdirectories for executables
add_subdirectory(src/game)
add_subdirectory(src/editor)

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

# Copy Data directory to build folder for convenience
add_custom_target(copy-data ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/data
        ${CMAKE_CURRENT_BINARY_DIR}/data
    COMMENT "Copying Data directory to build folder"
)

# Install rules for distribution
install(TARGETS game editor
    RUNTIME DESTINATION .
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data
    DESTINATION .
    PATTERN ".DS_Store" EXCLUDE
)

# Install runtime dependencies (DLLs on Windows)
if(WIN32)
    install(CODE [[
        file(GET_RUNTIME_DEPENDENCIES
            EXECUTABLES
                "${CMAKE_INSTALL_PREFIX}/game.exe"
                "${CMAKE_INSTALL_PREFIX}/editor.exe"
            RESOLVED_DEPENDENCIES_VAR _r_deps
            UNRESOLVED_DEPENDENCIES_VAR _u_deps
            DIRECTORIES
                "${CMAKE_BINARY_DIR}"
                "${CMAKE_PREFIX_PATH}/bin"
        )
        foreach(_file ${_r_deps})
            file(INSTALL
                DESTINATION "${CMAKE_INSTALL_PREFIX}"
                TYPE SHARED_LIBRARY
                FOLLOW_SYMLINK_CHAIN
                FILES "${_file}"
            )
        endforeach()
    ]])
endif()

# Print summary
message(STATUS "SDL2 include: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2_ttf include: ${SDL2_TTF_INCLUDE_DIRS}")
message(STATUS "SDL2_image include: ${SDL2_IMAGE_INCLUDE_DIRS}")
